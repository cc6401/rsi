<?php

/*
 * switch out the contents of $primary_links according to who is logged in
 * primary links is already set
 */
function cforge_subtheme_preprocess_page($variables) {
  global $user;
  if (user_access('committee') || !$logged_in) {
    $anon = '<div class="wrap-center">'.menu_tree('visitors') .'</div>';
    if ($variables['logged_in']) {
      $variables['primary_links'] .= $anon;
    }
    else {
      $variables['primary_links'] = $anon;
    }
  }
}

/*
 * Modification to help refresh imagecache pics after they've been changed
 */
function cforge_subtheme_imagecache($presetname, $path, $alt = '', $title = '', $attributes = NULL, $getsize = TRUE) {
  // Check is_null() so people can intentionally pass an empty array of
  // to override the defaults completely.
  if (is_null($attributes)) {
    $attributes = array('class' => 'imagecache imagecache-'. $presetname);
  }
  if ($getsize && ($image = image_get_info(imagecache_create_path($presetname, $path)))) {
    $attributes['width'] = $image['width'];
    $attributes['height'] = $image['height'];
  }

  $attributes = drupal_attributes($attributes);
  $imagecache_url = imagecache_create_url($presetname, $path);
  //added by matslats 
  if (arg(0)=='user') $imagecache_url .= '?';
  return '<img src="'. $imagecache_url .'" alt="'. check_plain($alt) .'" title="'. check_plain($title) .'" '. $attributes .' />';
}
