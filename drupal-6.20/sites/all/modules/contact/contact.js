(function ($) {

/**
 * Prepopulate form fields with information from the visitor cookie.
 */
Drupal.behaviors.fillUserInfoFromCookie = function (context) {
  $('form.user-info-from-cookie:not(.user-info-from-cookie-processed)').each(function () {
    var formContext = this;
    $.each(['name', 'mail', 'homepage'], function () {
      var $element = $('[name=' + this + ']', formContext);
      var cookie = $.cookie('Drupal.visitor.' + this);
      if ($element.length && cookie) {
        $element.val(cookie);
      }
    });
    $(this).addClass('user-info-from-cookie-processed');
  });
};

})(jQuery);
