(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.menuDrops =  {
    attach: function(context) {
      $(context).find('#division-links > ul').menuDrops();
    }
  }
})(jQuery, Drupal, this, this.document);
