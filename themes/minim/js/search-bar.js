(function ($, Drupal, window, document) {
  Drupal.behaviors.SearchBar =  {
    attach : function(context, settings) {
      $('#block-secondarynavigation a').filter(function(index) { return $(this).text() === "Search"; }).click(
        function(e) {
          $('.search-block-form').slideToggle();
          e.preventDefault();
        }
      );
    }
  }
})(jQuery, Drupal, this, this.document);
