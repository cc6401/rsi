<?php
// $Id: views_handler_field_other_participant.inc,v 1.1.2.2 2010/12/22 20:21:51 matslats Exp $

/**
 * @file
 * Field handler to allow linking to a payer's user page
 * @ingroup views_field_handlers
 */
class views_handler_field_other_participant extends views_handler_field {
  
  function construct() {
    parent::construct();
    if ($this->definition['group'] == t('Exchanges')) {
      $this->additional_fields['payer_uid'] = 'payer_uid';
      $this->additional_fields['payee_uid'] = 'payee_uid';
    }
  }

  function options(&$options) {
    parent::options($options);
    $options['link_to_other'] = TRUE;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    if ($this->definition['group'] == t('Exchanges')) {
      $form['link_to_other'] = array(
        '#title' => t("Link this field to the user"),
        '#type' => 'checkbox',
        '#default_value' => $this->options['link_to_other'],
      );
    }
  }

  function render_link($data, $values) {
    $name = theme('username', user_load($data));
    if (!$this->options['link_to_other']) {
      $name = strip_tags($name);
    }
    return $name;
  }
  
  function query() {
    //this is needed because the address of this function implies a db field which doesn't exist
    //see mc_display.views.inc $data['mc_exchanges']['participant']
    $this->ensure_my_table();
  }

  function render($values) {
    if (isset($this->view->argument['participant']) && count($this->view->args)) {
      $key = array_search('participant', array_keys($this->view->argument));
      if ($key !== FALSE) {
        $uid = $this->view->args[$key];
        $result = $values->mc_exchanges_payee_uid == $uid ?
          $values->mc_exchanges_payer_uid :
          $values->mc_exchanges_payee_uid;
        return $this->render_link($result, $values);
      }
    }
    return '-';
  }
}