<?php 
// $Id: template.php,v 1.13.2.5 2008/02/23 16:27:23 derjochenmeyer Exp $

/**
 * Sets the body-tag class attribute.
 *
 * Adds 'sidebar-left', 'sidebar-right' or 'sidebars' classes as needed.
 */
function phptemplate_body_class($left, $right) {
  if ($left != '' && $right != '') {
    $class = 'sidebars';
  }
  else {
    if ($left != '') {
      $class = 'sidebar-left';
    }
    if ($right != '') {
      $class = 'sidebar-right';
    }
  }

  if (isset($class)) {
    print ' class="'. $class .'"';
  }
}



function fourseasons_adminwidget($scripts) {

  if (empty($scripts)) { 
    print '
    <script type="text/javascript" src="'.base_path().'misc/jquery.js"></script>';
  }
    
  print '
    <script type="text/javascript">
    function toggle_style(color) {
      $("#header-image").css("background-color", color);
      $("#header-image").css("background-image", "none");
      $("h1").css("color", color);
      $("h2").css("color", color);
      $("h3").css("color", color);
      $("#headline a").css("color", color);
    }
    </script>
  
    <div id="farben">
      <span>try another color: </span>
      <a href="#" style="background-color:#FF9900;" onclick="toggle_style(\'#FF9900\');"></a>
      <a href="#" style="background-color:#003366;" onclick="toggle_style(\'#003366\');"></a>
      <a href="#" style="background-color:#990000;" onclick="toggle_style(\'#990000\');"></a>
      <a href="#" style="background-color:#CCCCCC;" onclick="toggle_style(\'#CCCCCC\');"></a>
      <a href="#" style="background-color:#006699;" onclick="toggle_style(\'#006699\');"></a>
      <a href="#" style="background-color:#000000;" onclick="toggle_style(\'#000000\');"></a>
    </div>

    <div id="font">
      <span style="margin-left:20px;">try another fontsize: </span>
      <a href="#" onclick="$(\'body\').css(\'font-size\',\'60%\');">60%</a>
      <a href="#" onclick="$(\'body\').css(\'font-size\',\'70%\');">70%</a>
      <a href="#" onclick="$(\'body\').css(\'font-size\',\'80%\');">80%</a>
      <a href="#" onclick="$(\'body\').css(\'font-size\',\'90%\');">90%</a>
    </div>
  ';
  
  if (arg(0) == 'admin' && arg(1) == 'build' && arg(2) == 'themes') { 
    print '<img src="http://www.kletterfotos.de/autor.php">';
  }

}


/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    return '<div class="breadcrumb">'. implode(' &rsaquo; ', $breadcrumb) .'</div>';
  }
}

/**
 * Allow themable wrapping of all comments.
 */
function phptemplate_comment_wrapper($content, $node) {
  if (!$content || $node->type == 'forum') {
    return '<div id="comments">'. $content .'</div>';
  }
  else {
    return '<div id="comments"><h2 class="comments">'. t('Comments') .'</h2>'. $content .'</div>';
  }
}


/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {
  $vars['tabs2'] = menu_secondary_local_tasks();

  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

function phptemplate_comment_submitted($comment) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $comment),
      '!datetime' => format_date($comment->timestamp)
    ));
}

function phptemplate_node_submitted($node) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}

/*
 * theme_table($header, $rows, $attributes = array(), $caption = NULL)
 * includes/theme.inc, line 757
 * we modify this to give each table a class and to wrap it into a div
 * thus we can add "overflow: auto" to show scrollbars
 */
function phptemplate_table($header, $rows, $attributes = array(), $caption = NULL) {

  $output = '<div class="tablewrapper">';
  $output .= '<table'. drupal_attributes($attributes) ." class=\"tableclass\">\n";

  if (isset($caption)) {
    $output .= '<caption>'. $caption ."</caption>\n";
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    $output .= ' <thead><tr>';
    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }
    $output .= " </tr></thead>\n";
  }

  // Format the table rows:
  $output .= "<tbody>\n";
  if (count($rows)) {
    $flip = array('even' => 'odd', 'odd' => 'even');
    $class = 'even';
    foreach ($rows as $number => $row) {
      $attributes = array();

      // Check if we're dealing with a simple or complex row
      if (isset($row['data'])) {
        foreach ($row as $key => $value) {
          if ($key == 'data') {
            $cells = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cells = $row;
      }

      // Add odd/even class
      $class = $flip[$class];
      if (isset($attributes['class'])) {
        $attributes['class'] .= ' '. $class;
      }
      else {
        $attributes['class'] = $class;
      }

      // Build row
      $output .= ' <tr'. drupal_attributes($attributes) .'>';
      $i = 0;
      foreach ($cells as $cell) {
        $cell = tablesort_cell($cell, $header, $ts, $i++);
        $output .= _theme_table_cell($cell);
      }
      $output .= " </tr>\n";
    }
  }

  $output .= "</tbody></table>\n";
  $output .= "</div>\n";
  return $output;
} 



