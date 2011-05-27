<?php

/**
 * @file
 * Override access of core contact link field.
 */
/**
 * A field that links to the user contact page, if access is permitted.
 */
class contact_handler_field_contact_link extends views_handler_field_contact_link {
  // Views isn't aware of the new user contact permission.
  function access() {
    return user_access('access user contact forms');
  }
}
