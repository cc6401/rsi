<?php
// $Id: page.tpl.php,v 1.7.2.8 2008/02/22 18:11:13 derjochenmeyer Exp $
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" <?php if (isset($language->dir)) { print 'dir="'.$language->dir.'"'; } ?>>
  <head>
    <title><?php print $head_title ?></title>
    <?php print $head ?>
    <?php print $styles ?>
    <?php print $scripts ?>
  <!--[if lt IE 7]>
  <style type="text/css" media="all">@import "<?php print base_path() . path_to_theme(); ?>/fix-ie.css";</style>
  <![endif]-->
</head>

<body <?php print phptemplate_body_class($left, $right); ?>>

<div id="pagewrapper">

  <?php print fourseasons_adminwidget($scripts); ?>


  <div id="headline">
    <?php
      if ($site_slogan) {
        $site_slogan = '<div id="site-slogan">'.$site_slogan.'</div>';
      } 
      else {
        $site_slogan = '';
      }
      
      if ($logo || $site_name) {
        print '<a href="'. check_url($base_path) .'" title="'. $site_name .'">';
        if ($logo) {
          print '<img src="'. check_url($logo) .'" alt="'. $site_title .'" id="logo" />';
        }
        print $site_name .'</a>';
        print $site_slogan;
      } else {
        print '<div style="clear:both; height:20px;"></div>';
      }
    ?>
  </div>
  
  <?php 
    foreach($primary_links as $key => $value ) {
      if (ereg('active', $key)) {
        $primary_links[$key]['attributes']['class'] = "active";
      }
    } 
  ?>

  <div id="navigation-primary">
        <?php if (isset($primary_links)) : ?>
          <?php print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
        <?php endif; ?>
    <div style="clear:both;"></div>
  </div>

  <div id="navigation-secondary">
        <?php 
          if (isset($secondary_links) && !empty($secondary_links)) {
            print theme('links', $secondary_links, array('class' => 'links secondary-links'));
          }
          else {
            print '<ul class="links secondary-links"><li style="border:none;">&nbsp;</li></ul>';
          }
        ?>
    <div style="clear:both;"></div>
  </div>

  <div id="header-image">
    <?php
      if (!empty($mission)) {
        print '<div id="site-mission">'.$mission.'</div>';
      }
    ?>
  </div>


  <div id="navigation-breadcrumb">
  <?php if ($breadcrumb) { print $breadcrumb; } else { print '<div class="breadcrumb"><a href="#">&nbsp;</a></div>'; } ?>
  </div>

  <div style="clear:both;"></div>
  <div id="contentwrapper">

    <?php if ($left): ?>
      <div id="sidebar-left" class="sidebar">
        <?php if ($search_box): ?><div class="block block-theme"><?php print $search_box ?></div><?php endif; ?>
        <?php print $left ?>
      </div>
    <?php endif; ?>

    <div id="middle-content">
      <div class="content-padding">
          <?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
          <?php if ($title): print '<h2'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h2>'; endif; ?>
          <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; ?>
          <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
          <?php if ($show_messages && $messages): print $messages; endif; ?>
          <?php print $help; ?>

          <?php print $content ?>
          <span class="clear"></span>
          <?php print $feed_icons ?>
          <div style="clear:both;"></div>
      </div>
    </div>

    <?php if ($right): ?>
      <div id="sidebar-right" class="sidebar">
        <?php if (!$left && $search_box): ?><div class="block block-theme"><?php print $search_box ?></div><?php endif; ?>
        <?php print $right ?>
      </div>
    <?php endif; ?>
  </div>

  <div style="clear:both;"></div>

  <div id="footer"><?php print $footer ?></div> 

  <div id="footer-message"><?php print $footer_message ?></div> 

</div>

<?php print $closure ?>

</body>
</html>