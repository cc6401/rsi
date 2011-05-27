<?php 
 /* 
 * shows a members address and offline contact details
 * variables:
 * 
 * $phone1 (optional)
 * $phone2 (optional)
 * $email
 * $address, a multiline adress (optional)
 * $responsibility, a profile field (optional)
 * $locality, a code such as a postal code
 * $name, username (themed)
 * $categories, a list of offer/want categories this user has nodes in.
 * $terms, a list of term objects for above
 */
?>

<div class = "offline-contact">
  <strong><?php print $name; ?></strong>
  <?php if ($responsibililty) print '<br />('. $responsibililty .')'; ?>
  <br /><pre><?php print $address; ?></pre>
  <br /><?php if ($phone1) print $phone1; ?>
  <?php if ($phone2) print ' '. t('or').' '. $phone2; ?>
  <?php if(count($categories)) print '<br />'. implode(', ', $categories); ?>
</div>
