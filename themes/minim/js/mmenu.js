(function($) {
  Drupal.behaviors.mmenu = {
    attach: function() {
      if (drupalSettings.mmenu) {
        var $trigger = $('<a/>').attr('href', '#mobile-menu').addClass('trigger mmenu-trigger').text('Main Navigation');
        $('#block-secondarynavigation').prepend($trigger);
        var $mobileMenu = $('<nav/>').attr('id', 'mobile-menu').appendTo('body');
        $mobileMenu.append($(drupalSettings.mmenu));
        $mobileMenu.mmenu({slidingSubmenus: false});
      }
    }
  };
})(jQuery);
