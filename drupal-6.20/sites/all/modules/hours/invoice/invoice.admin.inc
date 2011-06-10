<?php
// $Id: invoice.admin.inc,v 1.1 2009/09/14 18:41:37 axlroach Exp $
/**
 * @file
 * Invoice administration.
 */

function invoice_admin_settings($context) {
  $form = array();


  global $user;
  
  $account = user_load($user->uid);
  
  $result = db_query("SELECT * FROM {user_invoice_settings} WHERE uid = %d", $account->uid);
  if ($row = db_fetch_object($result)) {
    $default_invoicer = $row->invoicer;
    $default_invoicee = $row->invoicee;
    $default_invoice_for = $row->invoice_for;
    $default_payment_terms = $row->payment_terms;
    $default_hourly_rate = $row->hourly_rate;
    $default_currency_symbol = $row->currency_symbol;
  }

  // User info
  $form['account'] = array(
    '#type' => 'value',
    '#value' => $account,
  );
  
  // Textarea for invoicer:
  $form['invoicer_filter']['invoicer'] = array(
    '#type' => 'textarea',
    '#title' => t('From'),
    '#rows' => 6,
    '#columns' => 10,
    '#default_value' => isset($default_invoicer) ? $default_invoicer : '',
    '#description' => t('The From field at the top of your invoice.'),
  );
  
  // Textarea for invoicee:
  $form['invoicee_filter']['invoicee'] = array(
    '#type' => 'textarea',
    '#title' => t('To'),
    '#rows' => 6,
    '#columns' => 10,
    '#default_value' => isset($default_invoicee) ? $default_invoicee : '',
    '#description' => t('The To field at the top of your invoice.'),
  );
  
  
  // Textfield for for:
  $form['invoice_for'] = array(
    '#type' => 'textfield',
    '#title' => t('For'),
    '#size' => 50,
    '#maxlength' => 255,
    '#default_value' => isset($default_invoice_for) ? $default_invoice_for : 'Professional Services',
    '#description' => t('The for tag in your invoice (ie - Professional Services).'),
  );

  // Textfield for payment terms:
  $form['payment_terms'] = array(
    '#type' => 'textfield',
    '#title' => t('Payment Terms'),
    '#size' => 50,
    '#maxlengh' => 255,
    '#default_value' => 'Due Upon Receipt',
    '#default_value' => isset($default_payment_terms) ? $default_payment_terms : 'Due Upon Receipt',
    '#description' => t('The payment terms for your invoice (ie - Due Upon Receipt).'),
  );
  
  // Textfield for hourly rate:
  $form['hourly_rate'] = array(
    '#type' => 'textfield',
    '#title' => t('Hourly Rate'),
    '#size' => 50,
    '#maxlength' => 5,
    '#default_value' => isset($default_hourly_rate) ? $default_hourly_rate : '',
    '#description' => t('Your hourly rate with no currency symbol.'),
  );
  
  // Textfield for currency symbol
  $form['currency_symbol'] = array(
    '#type' => 'textfield',
    '#title' => t('Currency Symbol'),
    '#size' => 1,
    '#maxlength' => 1,
    '#default_value' => isset($default_currency_symbol) ? $default_currency_symbol : '',
    '#description' => t('The currency symbol that should be displayed for totals on your invoice.')
  );
  
  $form['#submit'][] = 'invoice_admin_settings_submit';
  
  return system_settings_form($form);
}

/*
 * Form submission handler
 */
function invoice_admin_settings_submit($form, &$form_state) {
  $form_values = $form_state['values'];

  $result = db_query("SELECT count(*) as count FROM {user_invoice_settings} WHERE uid = %d", $form_values['account']->uid);
  if ($row = db_fetch_object($result)) {
    if ($row->count) {
      db_query(
        "UPDATE {user_invoice_settings} "
      ."set invoicer = '%s', "
      ."invoicee = '%s', "
      ."invoice_for = '%s', "
      ."payment_terms = '%s', "
      ."hourly_rate = '%s', "
      ."currency_symbol = '%s'"
      ."WHERE uid = %d",
      check_plain($form_values['invoicer']),
      check_plain($form_values['invoicee']),
      check_plain($form_values['invoice_for']),
      check_plain($form_values['payment_terms']),
      check_plain($form_values['hourly_rate']),
      check_plain($form_values['currency_symbol']),
      $form_values['account']->uid
      );
    }
    else {
      db_query(
        'INSERT INTO {user_invoice_settings} (uid, invoicer, invoicee, invoice_for, payment_terms, hourly_rate, currency_symbol) '
          ."VALUES (%d, '%s', '%s', '%s','%s', '%s', '%s')",
        $form_values['account']->uid,
        check_plain($form_values['invoicer']),
        check_plain($form_values['invoicee']),
        check_plain($form_values['invoice_for']),
        check_plain($form_values['payment_terms']),
        check_plain($form_values['hourly_rate']),
        check_plain($form_values['currency_symbol'])
      );
    }
  }
  $form_state['redirect'] = 'admin/invoice/settings';
}
