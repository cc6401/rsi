$Id 

-- SUMMARY --

The Invoice module creates a content type called 'invoice'.  This 
module uses time entry data from the Hours module to create invoices.

For a full description of the module, visit the project page:
  http://drupal.org/project/uc_civicrm_profile_pane

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/uc_civicrm_profile_pane


-- REQUIREMENTS --
hours

-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

* Configure module settings in Administer >> Invoice Settings
  - Users will see a textarea called 'From'.  This is meant
    to hold the name and contact info for the invoicer.

  - Users will see a textarea called 'To'.  This is meant         
    to hold the name and contact info for the invoicee.

  - Users will see a textfield called 'For'.  This is meant
    to store what the invoice is for.  i.e. 'Services Rendered'.

  - Users will see a textfield called 'Hourly Rate'.  This is meant
    to store the hourly wage paid to this user.

  - Users will see a textfield called 'Currency Symbol'.  This is meant
    to store the symbol used to denote the type of currency to be paid
    to this user.  i.e. '$'.

-- CONTACT -- 

Current maintainers:
* A. J. Roach - http://drupal.org/user/35008

This project has been sponsored by:
* CIVICACTIONS, LLC

  Changing the world one node at a time!
