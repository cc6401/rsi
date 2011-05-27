<?php
// $Id: views_handler_filter_mc_exchange_types.inc,
/**
 * Filter handler for exchange types
 */
class views_handler_filter_mc_exchange_types extends views_handler_filter_many_to_one {

  //this is waiting for a suitable hook function so that modules can declare their own exchange types.
  function get_value_options() {
    $types = module_invoke_all('exchange_type_info');
    foreach ($types as $type => $info) {
      if ($info['title']) {
        $this->value_options[$type] = $info['title'];
      }
    }
  }
}
