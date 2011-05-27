<?php
//these are here instead of the preprocess funcntion for ease of translation
  $classes = array();
  if ($node->promote) {
    $classes[] = 'completed';
    if ($node->uid != 1) {
      $suffix = '<p>'. t('!user completed this', array('!user' => theme_username(user_load($node->uid)))) .'</p>';
    }
  }
  elseif ($node->uid == 1) {
    $classes[] = 'open';
  }
  else {
    $classes[] = 'committed';
    $suffix = '<p>'.t('!user committed to this.', array('!user' => theme_username(user_load($node->uid)))) .'</p>';
  }
?>
<!-- start node-community_task.tpl.php -->
<div id="node-<?php print $node->nid; ?>" class="node<?php print " node-" . $node->type; ?> <?php print implode(' ', $classes) ?>">
<?php if (!$page && $title): ?>
  <h3 class="title"><a href="<?php print $node_url; ?>" title="<?php print $title; ?>"><?php print $title; ?></a></h3>
<?php endif; ?>
<?php if ($submitted): ?>
  <div class="info"><?php print $picture; ?>
  </div>
<?php endif; ?>
<div class="content"><?php print $content.$suffix; ?></div>
</div><!-- end node-community_task.tpl.php -->