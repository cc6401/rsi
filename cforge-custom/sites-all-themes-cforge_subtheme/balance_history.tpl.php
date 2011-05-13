<?php

//this is calcluated as 2048 max chars in a google charts url - 250 characters for all the other data divided by 13 characters per chart-point
define ('MAX_CHART_POINTS', 140);

 /*
  * Balance History Google Chart 
  * Takes data in the format below and outputs an <img> tag for a google chart.
  * Feel free to tweak the initial variables
  * //TODO This could be cached.
  *
  * $account = User Obj
  * $histories = array(
  *   '$cid' = array(
  *     '$unixtime' => $balance
  *     '$unixtime' => $balance
  *     etc...
  *   )
  * );
  * $extent = 'limits' or 'balance'
  */
$dimensions = array('x' => 350, 'y' => 280);
$lines = $line_styles = $line_colors = $maxes = $mins = array();

//this loop draws one line for each currency
foreach ($histories as $cid => $history){
  $currency = node_load($cid);
  $times = array();
  $values = array();
  $first_time = array_shift(array_keys($history));
  //The system will choose here between three smoothing mechanisms, to make the best use fo the 2k URL limits of google charts.
  if (count($history)*2 < MAX_CHART_POINTS) {
    //unsmoothing mechanism, the true picture - adds intermediate points to produce perpendicular lines
    //make two points for each point, then slip the x against the y to make the step effect
    while (list($t, $bal) = each($history)){
      //subtract the first time to reduce the number of chars - should save about 3 per point
      $t1 = intval(($t - $first_time) / $dimensions['x']);
      //we could go further to reduce the number of chars and divide the time (unixtime) by something arbitrary,
      //like the number of pixels in the x axis
      $times[]=$t1;
      $times[]=$t1;
      $values[]=$bal;
      $values[]=$bal;
    }
    //remove the first time and the last value
    array_shift($times);
    array_pop($values);
  }
  //second smoothing mechanism, resample if there are too many points
  elseif (count($history) > MAX_CHART_POINTS) {
    //we can sample the array by a factor of an integer only
    $sample_frequency = ceil(count($history) / MAX_CHART_POINTS);
    //make an array with every possible value - approx one for every pixel
    $previous_time = array_shift($times);
    $bal = array_shift($history);
    $all_points[$previous_time] = $bal;
    while ($time = array_shift($times)) {
      while ($previous_time < $time) {//adding the in between points
        $all_points[$previous_time] = $bal;
        $previous_time++;
      }
      $bal = array_shift($history);
      $all_points[$previous_time] = $bal;
    }
    unset($points[$cid]);
    //$all_points now contains a value for every pixel time interval, ready for sampling
    //we reverse this array to be sure to sample the final value, which may be only a few seconds ago, so might otherwsie be sampled out
    $reverse_points = array_reverse($all_points, TRUE);
    foreach ($reverse_points as $t=>$eachpoint){
      if (fmod($j, $sample_frequency) == 0){
        $values[$t-$first_time] = $eachpoint;
      }
      $j++;
    }
    $times = array_keys($values);
  } else { //using given data
    //draws straight lines between the points
    foreach ($history as $time => $value) {
      $values [$time - $first_time] = $value;
    }
    $times = array_keys($values);
  }
  //make the url encoded line from the x and y values
  $lines['mainline'. $cid] = implode(',',$times) .'|'. implode(',', $values);
  $line_styles['mainline'.$cid] = 2;

  $maxes[] = max($values);
  $mins[] = min($values);
  
  if ($extent == 'limits' || !count($values)) {
    $limits = user_limits($account, $cid);
    $maxes[] = $limits['max'];
    $mins[] = $limits['min'];
  }

  $line_colors['mainline'. $cid] = $currency->data['color'];
  $curr_names[] = $currency->title;
}
//drupal_set_message('<pre>'.print_r($lines, 1).'</pre>');

//now put the line into the google charts api format
$params = array(
  'cht' => 'lxy',
  'chs' => implode('x', $dimensions),
  'chd' => 't:' . @implode('|', $lines),
  //optional parameters
  'chxt' => 'x,y', //needed for axis labels
  'chls' => implode('|', $line_styles),
  'chco' => implode(',', $line_colors),
);
if (count($lines) > 1) {
  $params['chdl'] = implode('|', $curr_names);
  $params['chdlp'] = 'b';
}

$max = max($maxes);
$min = min($mins);

if ($min != 0) { //0.5 means half way up, 0.6 must be larger than 0.5, thickness, priority
  $params['chm'] = "h,dddddd,0,". 1-abs($min)/(abs($min)+$max) .":1:1,1,1";
}
$params['chds'] = implode(',',array(-1, array_pop($times)+1 ,$min, $max));
$params['chxl'] = '0:|' . date('M y', $first_time) . '|' . t('Now') . '|1:|' . $min . '|' . $max;



if ($legend)$params['chtt'] = $legend;

//cleaner than http_build_query
foreach ($params as $key=>$val) {
  $args[] = $key . '=' . $val;
}

$url =  GOOGLE_CHARTS_URI .implode('&', $args);
if (strlen($url) > 2048) {
  watchdog('mcapi', "Error creating balance chart: url to google charts exceeded 2048 charts.");
  drupal_set_message("Error creating balance chart: url to google charts exceeded 2048 charts.");
}

//can't use theme_image because it checks for the presence of a file
print '<img align="right" src="' . $url . '" alt="' . $legend . '" title="' . $legend . '" class="chart" />';