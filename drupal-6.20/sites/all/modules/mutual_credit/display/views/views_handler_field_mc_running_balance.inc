<?php
// $Id: views_handler_field_mc_running_balance.inc,v 1.1.2.2 2010/12/22 20:21:51 matslats Exp $

/**
 * @file
 * Field handler to allow linking to a payee's user page
 * @ingroup views_field_handlers
 */
class views_handler_field_mc_running_balance extends views_handler_field {

  function construct() {
    parent::construct();
    //this is added by something else, at least usually
    //$this->additional_fields['cid'] = 'cid';

    //THIS DOESN'T WORK but would be nice for hiding pending running balances
    $this->additional_fields['state'] = 'state';
  }

  function option_definition() {
    $options = parent::option_definition();
    if (module_exists('mc_signatures')) {
      $options['count_pending'] = array('default' => FALSE);
      return $options;
    }
    return array();
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    if (module_exists('mc_signatures')) {
      $form['count_pending'] = array(
        '#type' => 'checkbox',
        '#title' => t('Count pending exchanges'),
        '#description' => t('Include pending exchanges when calculating balance') . '(Not working, sorry)',
        '#default_value' => $this->options['count_pending'],
      );
    }
  }
  
  function query() {
    //this is needed because the address of this function implies a db field which doesn't exist
    //see mc_display.views.inc $data['mc_exchanges']['participant']
    $this->ensure_my_table();
  }

  function render($values) {
    if (isset($this->view->argument['participant']) && count($this->view->args)) {
      $states = array(EXCHANGE_STATE_FINISHED);
      $state = db_result(db_query("SELECT state FROM {mc_exchanges} WHERE nid = %d", $values->nid));
      //the transaction is pending and the options don't count pending, then leave this field blank
      if ($state && !$this->options['count_pending']) return;

      if ($this->options['count_pending'] && $state == EXCHANGE_STATE_FINSHED) {
        $states[] = EXCHANGE_STATE_FINISHED;
      }

      $states = implode(',', $states);
      $key = array_search('participant', array_keys($this->view->argument));
      if ($key !== FALSE) {
        $uid = $this->view->args[$key];
        //could these be incorporated into the query itself?
        $outgoing = db_result(db_query("SELECT sum(quantity) from {mc_exchanges} WHERE payer_uid = $uid AND state IN ($states) AND nid <= %d", $values->nid));
        $income = db_result(db_query("SELECT sum(quantity) from {mc_exchanges} WHERE payee_uid = $uid AND state IN ($states) AND nid <= %d", $values->nid));
        return theme('money', $income-$outgoing, $values->mc_exchanges_cid);
      }
    }
  }
}