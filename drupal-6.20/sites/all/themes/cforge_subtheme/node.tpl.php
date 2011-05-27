<?php // $Id$ ?>
<!-- start node.tpl.php -->
<div id="node-<?php print $node->nid; ?>" class="node<?php print " node-" . $node->type; ?><?php print $sticky ? ' node-sticky' : ''; ?>">
<?php if (!$page && $title): ?>
  <h2 class="title"><a href="<?php print $node_url; ?>" title="<?php print $title; ?>"><?php print $title; ?></a></h2>
<?php endif; ?>
<?php if ($links): ?>
  <div class="btn-links" style="float:right;"><?php print $links; ?></div>
<?php endif; ?>
<?php if ($submitted): ?>
  <div class="info"><?php print $picture; ?>
    <?php if ($terms): ?>
      <div class="btn-tags"><?php print $terms; ?></div>
    <?php endif; ?>
  </div>
<?php endif; ?>
<div class="content"><?php print $content; ?></div>
</div>
<!-- end node.tpl.php -->
