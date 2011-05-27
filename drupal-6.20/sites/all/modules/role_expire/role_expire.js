// $Id: role_expire.js,v 1.2 2009/06/03 19:42:37 bdziewierz Exp $ 

/**
 * @file
 * Role Expire js
 *
 * Set of jQuery related routines.
 */

$(document).ready(function() {
  $('input.role-expire-role-expiry').parent().hide();
  
  $('.role-expire-roles input.form-checkbox').each(function() {
    var textfieldId = this.id.replace("roles", "role-expire");

    // Move all expiry date fields under corresponding checkboxes
    $(this).parent().after($('#'+textfieldId).parent());
    
    // Show all expiry date fields that have checkboxes checked
    if ($(this).attr("checked")) {  
      $('#'+textfieldId).parent().show();
    }
   
  });
  
  $('.role-expire-roles input.form-checkbox').click(function() {
    var textfieldId = this.id.replace("roles", "role-expire");
    
    // Toggle expiry date fields
    if ($(this).attr("checked")) {
      $('#'+textfieldId).parent().show(200);
    } 
    else {
      $('#'+textfieldId).parent().hide(200);    
    }
  });
});