<?php
//$Id: 
/**
 * @file
 * Contains default views to supplement the offers/wants modules
 */

/**
 * Implementation of hook views_data().
 */
function mc_offer_want_views_data() {
  $data = array();
  $data['cc_offers_wants']['table']['group']  = t('Offers/Wants');
  $data['cc_offers_wants']['table']['base'] = array(
    'title' => t('Offers/wants'),
    'field' => 'nid',
    'help' => t('Offers and wants directory entries, created by members'),
  );
  $data['cc_offers_wants']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  return $data;
}

function mc_offer_want_views_handlers() {
  $handlers= array(
    'info' => array(
      'path' => drupal_get_path('module', 'transactions') .'/views',
    ),
    'handlers' => array(
      'views_handler_field_not_cc' => array(
        'parent' => 'views_handler_field'
      ),
      'views_handler_filter_not_cc' => array(
       'parent' => 'views_handler_filter_boolean_operator'
      ),
      'views_handler_filter_goods_not_services' => array (
        'parent' => 'views_handler_filter_boolean_operator'
      )
    )
  );
  return $handlers;
}

/**
 * Implementation of hook views_default_views().
 */
function mc_offer_want_views_default_views() {
  $php_filter = strval(db_result(db_query('SELECT format from {filter_formats} WHERE name = "PHP Code" ')));
  
  //USE THE FOLLOWING REGEX ON NEW VIEWS
  //Replace the the folloowing with  '\1' => t('\2')
  //'(label)' => '(.+)'
  //'(empty)' => '(.+)'
  //'(title)' => '(.+)'
  //'(header)', '(.+)'
  //'(footer)', '(.+)'
  
  //these should be ok if only one type is named
  $view = mc_directory_user_view($php_filter);
  $views[$view->name] = $view;
  
  $view = mc_directory_recent_offers_view($php_filter);
  $views[$view->name] = $view;
  $view = mc_directory_recent_wants_view($php_filter);
  $views[$view->name] = $view;
  $view = mc_directory_recent_view($php_filter);
  $views[$view->name] = $view;
  
  return $views;
}

function mc_directory_user_view($php_filter){
  
  $page_type_filter=array();
  $menu_title = t('Offers/Wants');
  $page_type_filter['offer'] = 'offer';
  
  //careful editing this because it contains variables
  $view = new view;
  $view->name = 'mc_directory_user';
  $view->description = t("offers/wants from a given user. (Doesn't work for wants only.)");
  $view->tag = 'offers/wants';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'user directory default', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => t('Description'),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'changed' => array(
      'label' => t('Date'),
      'date_format' => 'time ago',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => '',
      'text' => t('Edit'),
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
    'delete_node' => array(
      'label' => '',
      'text' => t('Delete'),
      'exclude' => 0,
      'id' => 'delete_node',
      'table' => 'node',
      'field' => 'delete_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'changed' => array(
      'order' => 'DESC',
      'granularity' => 'hour',
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'me',
      'wildcard_substitution' => 'My',
      'title' => '',
      'default_argument_type' => 'current_user',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'offer' => 0,
        'want' => 0,
        'transaction' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view directory',
  ));
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => 'type',
    'override' => 1,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'type' => 'type',
      'title' => 'title',
      'name' => 'name',
      'last_updated' => 'last_updated',
      'name_1' => 'name_1',
    ),
    'info' => array(
      'type' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_updated' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name_1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'name_1',
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => $page_type_filter,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'users',
      'field' => 'status',
      'override' => array(
        'button' => 'Remplacer',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('title', '');
  $handler->override_option('empty', t('No offers have been entered.'));
  $handler->override_option('header', '<h4>' . $menu_title . '</h4>');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('empty_format', '1');
  $handler->override_option('path', 'user/%/directory');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => $menu_title,
    'description' => '',
    'weight' => '1',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));


    $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
    $handler->override_option('filters', array(
      'type' => array(
        'operator' => 'in',
        'value' => array('want' => 'want'),
        'group' => '0',
        'exposed' => FALSE,
        'expose' => array(
          'operator' => FALSE,
          'label' => '',
        ),
        'id' => 'type',
        'table' => 'node',
        'field' => 'type',
        'override' => array(
          'button' => 'Use default',
        ),
        'relationship' => 'none',
      ),
    ));
    $handler->override_option('empty', t('No wants have been entered.'));
    $handler->override_option('empty_format', '1');
    $handler->override_option('header', '<h4>' . t('Member wants') . '</h4>');
    $handler->override_option('header_format', '2');
    $handler->override_option('header_empty', 0);
    $handler->override_option('footer_empty', 1);
    $handler->override_option('attachment_position', 'after');
    $handler->override_option('inherit_arguments', TRUE);
    $handler->override_option('inherit_exposed_filters', FALSE);
    $handler->override_option('displays', array(
      'page_1' => 'page_1',
      'default' => 0,
    ));
  
  //Keep this at the end of this display
  if ($php_filter) {
    $footer = "<?php //enable php module or delete this view footer";
    $footer .= "print theme('offers_wants_link', 'offer')";
    $footer .= " . theme('offers_wants_link', 'want')";
    $footer .= "; ?>";
    $handler->override_option('footer', $footer);
    $handler->override_option('footer_format', $php_filter);
  }
  
  return $view;  
}

function mc_directory_recent_view($php_filter) {
  $view = new view;
  $view->name = 'mc_directory_recent';
  $view->description = 'Directory Entries by published date';
  $view->tag = 'offers/wants';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'type' => array(
      'label' => t('Type'),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'name_1' => array(
      'label' => t('Category'),
      'link_to_taxonomy' => 0,
      'exclude' => 0,
      'id' => 'name_1',
      'table' => 'term_data',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => t('Description'),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => t('Member'),
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => t(''),
      'text' => 'Edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'name' => array(
      'order' => 'ASC',
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'changed' => array(
      'order' => 'DESC',
      'granularity' => 'hour',
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'name' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => t('Latest %1 offers'),
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 1,
      'add_table' => 0,
      'require_value' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'offer' => 0,
        'want' => 0,
        'requack' => 0,
        'transaction' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'offer' => 'offer',
        'want' => 'want',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => t(''),
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'users',
      'field' => 'status',
      'override' => array(
        'button' => 'Remplacer',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view directory',
  ));
  $handler->override_option('title', t('Latest directory entries'));
  $handler->override_option('footer', "");
  $handler->override_option('footer_format', '2');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', t('There are no entries in this category'));
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 0);
  $handler->override_option('use_more', 1);
  $handler->override_option('distinct', 0);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title_1' => 'title_1',
      'name' => 'name',
      'created' => 'created',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'title_1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  
  //Keep this at the end of this display
  if ($php_filter) {
    $handler->override_option('footer', "<?php //enable php module or delete this view footer
    print theme('offers_wants_link', 'offer') . theme('offers_wants_link', 'want'); ?>");
    $handler->override_option('footer_format', $php_filter);
  }

  $handler = $view->new_display('page', 'Latest directory page', 'page_1');
  $handler->override_option('fields', array(
    'title_1' => array(
      'label' => t('Description'),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title_1',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => t('Member'),
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'created' => array(
      'label' => t('Posted on'),
      'date_format' => 'custom',
      'custom_date_format' => 'd/m/y',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'edit_node' => array(
      'label' => t(''),
      'text' => 'Edit',
      'exclude' => 1,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  
  $handler->override_option('items_per_page', 20);
  $handler->override_option('path', 'directory/recent');
  if (variable_get('cc_ow_content_types', 'offers') == 'both') {
    $handler->override_option('menu', array(
      'type' => 'normal',
      'title' => t('All offers/wants'),
      'weight' => '19',
      'name' => 'navigation',
    ));
  }
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'latest directory block', 'block_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => t(''),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'uid' => array(
      'label' => t(''),
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('header', '');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 5);
  $handler->override_option('use_pager', '0');
  $handler->override_option('use_more', 0);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array());
  $handler->override_option('row_options', array(
    'inline' => array(
      'title' => t('title'),
      'uid' => 'uid',
    ),
    'separator' => '>',
  ));
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('footer', '');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('items_per_page', 25);
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'item_length' => 'title',
  ));
  $handler->override_option('path', 'directory/recent/%feed/');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
  ));
  $handler->override_option('displays', array(
    'default' => 'default',
    'page_1' => 'page_1',
    'block_1' => 'block_1',
  ));
  $handler->override_option('sitename_title', FALSE);
  
  return $view;
}

function mc_directory_recent_offers_view($php_filter) {
  $view = new view;
  $view->name = 'mc_directory_recent_offers';
  $view->description = t('Offers by published date');
  $view->tag = 'offers/wants';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => t('Description'),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => t('Member'),
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => t('Posted on'),
      'date_format' => 'custom',
      'custom_date_format' => 'd/m/y',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'edit_node' => array(
      'label' => t(''),
      'text' => 'Edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'changed' => array(
      'order' => 'DESC',
      'granularity' => 'hour',
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'tid' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => t('Offers') .': %1',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'taxonomy_term',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'add_table' => 0,
      'require_value' => 0,
      'reduce_duplicates' => 0,
      'set_breadcrumb' => 0,
      'id' => 'tid',
      'table' => 'term_node',
      'field' => 'tid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'currency' => 0,
        'offer' => 0,
        'want' => 0,
        'transaction' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    )
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'offer' => 'offer',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => t(''),
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'users',
      'field' => 'status',
      'override' => array(
        'button' => 'Remplacer',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view directory',
  ));
  $handler->override_option('title', t('Offers'));
  $handler->override_option('footer', "");
  $handler->override_option('footer_format', '1');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', t('There are no offers in this category'));
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('use_more', 1);
  $handler->override_option('distinct', 0);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title_1' => 'title_1',
      'name' => 'name',
      'created' => 'created',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'title_1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  
  //Keep this at the end of this display
  if ($php_filter) {
    $handler->override_option('footer', "<?php //enable php module or delete this view footer
    print theme('offers_wants_link', 'offer'); ?>");
    $handler->override_option('footer_format', $php_filter);
  }

  $handler = $view->new_display('page', t('Latest offers page'), 'page_1');
  $handler->override_option('path', 'directory/recent_offers');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => t('All offers'),
    'weight' => '19',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
  ));
  
  $handler = $view->new_display('block', 'latest offers block', 'block_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 5);
  $handler->override_option('use_pager', '0');
  $handler->override_option('use_more', 0);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array());
  $handler->override_option('row_options', array(
    'inline' => array(
      'title' => t('title'),
      'uid' => 'uid',
    ),
    'separator' => '>',
  ));
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('footer', '');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('items_per_page', 25);
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'item_length' => 'title',
  ));
  $handler->override_option('path', 'directory/recent_offers/%/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
  ));
  $handler->override_option('displays', array(
    'default' => 'default',
    'page_1' => 'page_1',
    'block_1' => 'block_1',
  ));
  $handler->override_option('sitename_title', FALSE);
  return $view;
}

function mc_directory_recent_wants_view($php_filter){
  $view = new view;
  $view->name = 'mc_directory_recent_wants';
  $view->description = 'Wants by published date';
  $view->tag = 'offers/wants';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => t('Description'),
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => t('Member'),
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => t('Posted on'),
      'date_format' => 'custom',
      'custom_date_format' => 'd/m/y',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'edit_node' => array(
      'label' => t(''),
      'text' => 'Edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'changed' => array(
      'order' => 'DESC',
      'granularity' => 'hour',
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'tid' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => t('Wants').': %1',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'taxonomy_term',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'add_table' => 0,
      'require_value' => 0,
      'reduce_duplicates' => 0,
      'set_breadcrumb' => 0,
      'id' => 'tid',
      'table' => 'term_node',
      'field' => 'tid',
      'validate_user_argument_type' => 'uid',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'want' => 'want',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => t(''),
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view directory',
  ));
  $handler->override_option('title', t('Wants'));
  $handler->override_option('header', "");
  $handler->override_option('footer_format', '1');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', t('There are no wants in this category'));
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('use_more', 1);
  $handler->override_option('distinct', 0);
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title_1' => 'title_1',
      'name' => 'name',
      'created' => 'created',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'title_1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  
  //Keep this at the end of this display
  if ($php_filter) {
    $handler->override_option('footer', "<?php //enable php module or delete this view footer
     print theme('offers_wants_link', 'want'); ?>");
    $handler->override_option('footer_format', $php_filter);
  }
  $handler = $view->new_display('page', 'Latest wants page', 'page_1');
  $handler->override_option('path', 'directory/recent_wants');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => t('All wants'),
    'weight' => '19',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'latest wants block', 'block_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 5);
  $handler->override_option('use_pager', '0');
  $handler->override_option('use_more', 0);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array());
  $handler->override_option('row_options', array(
    'inline' => array(
      'title' => t('title'),
      'uid' => 'uid',
    ),
    'separator' => '>',
  ));
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);

  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('footer', '');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('items_per_page', 25);
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'item_length' => 'title',
  ));
  $handler->override_option('path', 'directory/recent_wants/%/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => t(''),
    'weight' => 0,
  ));
  $handler->override_option('displays', array(
    'default' => 'default',
    'page_1' => 'page_1',
    'block_1' => 'block_1',
  ));
  $handler->override_option('sitename_title', FALSE);
  
  return $view;
}

