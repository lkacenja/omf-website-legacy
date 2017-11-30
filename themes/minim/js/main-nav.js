/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.MainNav =  {
    attach : function(context, settings) {
      $('li.division-link-56').not('li.bg-green').hover(
        function() {
          $( this ).addClass('bg-green');
        }, function() {
          $( this ).removeClass('bg-green');
        }
      );
      $('li.division-link-57').not('li.bg-red').hover(
        function() {
          $( this ).addClass('bg-red');
        }, function() {
          $( this ).removeClass('bg-red');
        }
      );
      $('li.division-link-58').not('li.bg-orange').hover(
        function() {
          $( this ).addClass('bg-orange');
        }, function() {
          $( this ).removeClass('bg-orange');
        }
      );
    }
  }
})(jQuery, Drupal, this, this.document);
