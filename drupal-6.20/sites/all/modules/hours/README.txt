$Id 

-- SUMMARY --

The Hours module creates a content type called 'hours'.  This 
content type is meant to be used primarily by independent 
contractors.  The 'hours' type represents a time entry.
The Hours module is useful for keeping track of billable 
hours, and can be used in conjunction with the invoice module
to generate invoices.

For a full description of the module, visit the project page:
  http://drupal.org/project/uc_civicrm_profile_pane

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/uc_civicrm_profile_pane


-- REQUIREMENTS --
date_api
date
date_popup

-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

* Configure module settings in Administer >> Hours Settings
  - Administers will see a 'send method'.  The default is on site, meaning
    that all hours will be stored in the database for Hours administrators.
    This will happen regardless of whether or not the other option, 'Email'
    is chosen.  If 'Email' is chosen, then the hours data will also be
    emailed.

  - Administers will see a text box where they may enter an email address.
    If 'Email' is selected as the 'send method' (see above), then hours 
    data will be sent to the email address entered here.

  Note that as of now, the 'Email' 'send method' is COMPLETELY untested.
  Use at your own risk.  If you discover problems, please submit an issue
  (or a patch ;) ).

-- CONTACT -- 

Current maintainers:
* A. J. Roach - http://drupal.org/user/35008

This project has been sponsored by:
* CIVICACTIONS, LLC

  Changing the world one node at a time!
