<?php
// $Id: views_handler_field_mc_trader.inc,v 1.1.2.2 2010/12/22 20:21:51 matslats Exp $

/**
 * @file
 * Field handler to allow linking to a payer's user page
 * @ingroup views_field_handlers
 */
class views_handler_field_mc_trader extends views_handler_field {

  function options(&$options) {
    parent::options($options);
    $options['link_to_trader'] = TRUE;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_trader'] = array('default' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_trader'] = array(
      '#title' => t("Link this field to the user"),
      '#type' => 'checkbox',
      '#default_value' => $this->options['link_to_trader'],
    );
  }

  function render_link($data, $values) {
    $name = theme('username', user_load($data));
    if (!$this -> options['link_to_trader']) {
      $name = strip_tags($name);
    }
    return $name;
  }

  function render($values) {
    return $this->render_link(check_plain($values->{$this->field_alias}), $values);
  }
}

