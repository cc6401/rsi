<?php
/*
 * we'll do the preprocessing here, rather than try to interrupt the normal node preprocessing hierarchy
 * which would be inefficient
 * We have access to all the normal node fields, and
 * $payer_uid        //uid of payer
 * $payee_uid        //uid of payee
 * $starter_uid      //uid of transaction initiator
 * $completer_uid    //uid of transaction completer
 * $cid              //nid of currency (0 unless currencies module installed)
 * $quantity         //quant of currency in transaction
 * $transaction_type //either incoming_confirm, outgoing_confirm, incoming_direct or outgoing_direct, or others
 * $quality          //transaction rating - reflects on the payee
 * $state            //1 = pending, 0 = completed, -1 = erased
*/
//the preprocess function
extract(preprocess_transaction_fields($node, $account->uid));

/*
 *  makes the following available
 * $submitted       //formatted date
 * $description     //the transaction title,
 * $payer           //name linked to payer profile
 * $payee           //name linked to payee profile
 * $starter         //name linked to starter profile
 * $completer       //name linked to completer profile
 * $notme           //name linked to whichever participant is not the current one
 * $amount          //formatted quantity
 * $balance         //formatted running balance
 * $rating          //themed rating
 * $transaction_link//title of transaction, linked to node
 * $classes         //array of css classes
 *
 */
//lumping all these together just makes the translation strings easier
$replacements = array(
  '!starter' => $starter,
  '!completer'=> $completer,
  '!amount' => $amount,
  '!transaction_link' => $transaction_link,
  '!payer' => $payer,
  '!payee' => $payee,
  '@submitted' => $submitted
);
if ($teaser) $classes[] = 'teaser';
elseif($page) $classes[] = 'page';
$currency = currency_load($cid);
?>

<div class="transaction <?php print implode(' ', $classes); ?>">
<?php
if ($teaser) { // this is a one liner
  switch($state) {
    case TRANSACTION_STATE_PENDING:
      if (substr($transaction_type, 0, 8) == 'outgoing') {
        print t("!starter will give !completer !amount for '!transaction_link'", $replacements);
      } else {
        print t("!starter will receive !amount from !completer for '!transaction_link'", $replacements);
      }
      break;
    case TRANSACTION_STATE_COMPLETED:
      print t("On @submitted, !payer gave !payee !amount for '!transaction_link'", $replacements);
      break;
    case TRANSACTION_STATE_DELETED:
      print t("On @submitted, !payer did not give !payee !amount for '!transaction_link'. (DELETED)'", $replacements);
  }

} else {
  $page_title = t('Transaction Certificate #@nid', array('@nid' => $nid));
  if ($state == TRANSACTION_STATE_PENDING) $page_title .= '-'. strtoupper(t('pending'));
  drupal_set_title($page_title);
  ?>
  <p>On <?php print $submitted; ?></p>
  <p><?php print $payer; ?>
   <?php if ($state == TRANSACTION_STATE_PENDING) print ' will pay '; else print ' paid '; ?>
   <?php print $payee; ?><br /><br />
   the sum of <span style="font-size:250%"> <?php print $amount . '<span style="line-height:115%"> ' . $currency->title; ?></span></p>
  <p>"<strong><?php print $description; ?></strong>"
   <?php if ($state == TRANSACTION_STATE_PENDING) print 'to be exchanged'; else print 'was exchanged'; ?><?php
    if ($rating) {
      print ", and $payer rated the transaction as '$rating'";
    }
}?><br /><br />
<?php print $links; ?>
</div>