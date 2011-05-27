<?php
// $Id: role_expire.views.inc,v 1.4 2009/09/23 19:31:21 stewsnooze Exp $

/**
 * @file
 * Role Expire Views hooks
 *
 * Views module integration with the role expire module
 */

/**
 * Implementation of hook_views_data().
 */
function role_expire_views_data() {
  $data['role_expire']['table']['group']  = t('User');

  $data['role_expire']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['role_expire']['expiry_timestamp'] = array(
    'title' => t('Role expiration time'),
    'help' => t('Time and date the role will expire.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  return $data;
}