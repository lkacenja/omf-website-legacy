(function ($) {
  Drupal.behaviors.rotator = {
    attach : function(context, settings) {
      // We append a dummy slide to allow the parent box to size appropriately
      var $dummy = $('<img/>').attr({width: 1500, id: "dummy", src: "/themes/minim/img/1500x400fff.gif"});
      var $wrapper = $('<div/>').addClass('dummy-slide').prepend($dummy);

      $('.view-slides .view-content').prepend($wrapper);

      $dummy.load(function() {
        $('.view-slides', context).once('rotator',
          function() {
            var $nav = $('<div/>').attr('id', 'rotator-nav-wrap').attr('class', 'clearfix bg-grey');
            $($nav).html('<div id="rotator-nav" class="center-block bg-grey"></div>');
  
            $(this).append($nav).find('.view-content').cycle({
	      pager: '#rotator-nav',
              delay: 5800,
              slideExpr: '.slider-wrap',
              slideResize: 0,
              pagerAnchorBuilder: function(idx, slide) {
                var pagerClass = '';
                switch (idx) {
                  case 0:
                    pagerClass += 'bg-green';
                  break;
                  case 1:
                    pagerClass += 'bg-red';
                  break;
                  case 2:
                    pagerClass += 'bg-orange';
                  break;
                }
                pagerClass += ' slide-'+ idx;
                
                return '<a href="#" class="'+ pagerClass +'"></a>';
              }
            });
          }
        );
      });
    }
  }
})(jQuery);
