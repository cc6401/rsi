<?php
// $Id$
//MUST BE COPIED TO THEME DIRECTORY

/**
 * @file
 * Default cforge_print module template
 *
 * @ingroup print
 */
global $language;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language; ?>" xml:lang="<?php print $language->language; ?>">   
  <head>
    <?php print $head; ?>
    <link href="/<?php print drupal_get_path('module', 'cforge_print'); ?>/cforge_print.css" media="all" rel="stylesheet" type="text/css">
    <?php print $favicon; ?>
    <meta name="robots' content='noindex, nofollow, noarchive' />
  </head>
  <body onload="window.print();">
    <div><img class='print-logo' src='<?php print $logo; ?>' alt='' />
    <h1><?php print $sitename .' '. $title; ?></h1>
    <div id="cforge_print-sitename"><h3>Published on <?php print $sitename; ?></h3></div>
    <?php print $content; ?>
  </body>
</html>