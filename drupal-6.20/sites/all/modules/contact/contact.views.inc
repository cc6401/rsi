<?php

/**
 * @file
 * Declare Views handlers.

/**
 * Implements hook_views_data().
 */
function contact_views_data() {
  $data['users']['contact'] = array(
    'field' => array(
      'title' => t('Link to contact page'),
      'help' => t('Provide a simple link to the user contact page.'),
      'handler' => 'contact_handler_field_contact_link',
    ),
  );
  return $data;
}

/**
 * Implements hook_views_handlers().
 */
function contact_views_handlers() {
  return array(
    'handlers' => array(
      'views_handler_field_contact_link' => array(
        'parent' => 'views_handler_field_user_link',
        'path' => drupal_get_path('module', 'views') . '/modules/contact',
      ),
      'contact_handler_field_contact_link' => array(
        'parent' => 'views_handler_field_contact_link',
      ),
    ),
  );
}
