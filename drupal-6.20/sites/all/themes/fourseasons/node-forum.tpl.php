<?php
    $account = user_load(array('uid'=>$node->uid));
?>

<div class="forum-topic">
  <div class="user-info">
    <div class="user-name"><?php print $account->name; ?></div>
    <?php print $picture ?>
    <div class="user-member"><?php print t('<strong>Member since:</strong><br /> !ago', array('!ago' => format_interval(time() - $account->created))); ?></div>  
    <div class="user-access"><?php print t('<strong>Last activity:</strong><br /> !ago', array('!ago' => format_interval(time() - $account->access))); ?></div>  
  </div>
  
  <div class="topic">
    <div class="topic-title"><?php print $node->title; ?></div>

    <?php if ($submitted): ?>
    <span class="submitted"><?php print t('Posted !date', array('!date' => format_date($node->created))); ?></span>
    <?php endif; ?> 

    <div class="topic-body"><?php print $node->body; ?></div>
  </div>
  <div style="clear:both;"></div>
  <?php print $links; ?>
</div>



