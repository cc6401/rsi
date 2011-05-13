<?
  $transactions_per_page = 10;
/* statement view
 * 
 * Presently we are only preprocessing transactions like this for the 'statement'
 * VARIABLES:
 * $transactions array, in ASCending order of node creation: 
 *   Each transaction looks like
 * 
array (
  [title] => gift from carl to darren
  [nid] => 44
  [payer_uid] => 3
  [payee_uid] => 4
  [starter_uid] => 3
  [completer_uid] => 4
  [cid] => 0
  [quantity] => -5
  [quality] => 2
  [state] => 0
  [created] => 1251757109
  [submitted] => Mon, 08/31/2009 - 22:18
  [transaction_type] => outgoing_direct
  [balance] => -5
  [expenditure] => theme(money $quantity...)
OR[income] => theme(money $quantity...)
  [class] => "debit quality2" //so you can theme according to the transaction direction and rating
  [description] => gift from carl to darren
  [starter] => <a href="/user/3" title="View user profile.">carl</a>
  [completer] => <a href="/user/4" title="View user profile.">darren</a>
  [amount] => theme(money $quantity...)
  [payee] => <a href="/user/3" title="View user profile.">carl</a>
  [payer] => <a href="/user/4" title="View user profile.">darren</a>
  [notme] => <a href="/user/4" title="View user profile.">darren</a>
  [transaction_link] => <a href="/node/44">gift from carl to darren</a>
  [actions] => some HTML links
)
 */
 drupal_set_title(username_responsibility($account));
 
  //need to delare the column headings, their order, and associated fields
  //array keys must correspond to the keys in the transaction objects
  $columns = array(
//    'submitted' => t('Date'),
    'transaction_link' => t('Description'), 
    'notme' => t('With'),
    //'amount' => t('Amount'),
    'income' => t('Income'),
    'expenditure' => t('Expenditure'),
    'balance' => t('Running Total'),
    'actions' => '',
  );
  if (!variable_get('cc_transaction_qualities', array())) unset ($columns['quality']);
  //put the given array into the columns declared to make a table
  foreach($transactions as $key => $transaction) {
    foreach ($columns as $field => $title){
      $rows[$key]['data'][$field] = $transaction[$field];
      $rows[$key]['class'] = $class;
    }
  }
  if (!isset($transaction->quality))unset ($columns['quality']);
  
  print theme('table', $columns, $rows) . 
    theme('pager', NULL, TRANSACTIONS_PER_PAGE, TRANSACTIONS_PAGER_ELEMENT);