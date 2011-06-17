<div class="comment<?php print ($comment->new) ? ' comment-new' : ''; print ($comment->status == COMMENT_NOT_PUBLISHED) ? ' comment-unpublished' : ''; print ' '. $zebra; ?>">

  <div class="clear-block">

  <?php if ($comment->new) : ?>
    <a id="new"></a>
    <span class="new"><?php print drupal_ucfirst($new) ?></span>
  <?php endif; ?>

  <?php print $picture ?>

    <h3><?php print $title ?></h3>

    <?php if ($submitted): ?>
      <span class="submitted"><?php print t('!date — !username', array('!username' => theme('username', $comment), '!date' => format_date($comment->timestamp))); ?></span>
    <?php endif; ?>
      
    <div class="content">
      <?php print $content ?>
    </div>

  </div>

  <?php if ($links): ?>
    <div class="links"><?php print $links ?></div>
  <?php endif; ?>
  <div style="clear:both;"></div>
</div>
