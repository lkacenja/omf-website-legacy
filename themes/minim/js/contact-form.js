(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.ContactForm =  {
    attach : function(context, settings) {
      if ($('.page-node-117 .ss-form-question:nth-child(3) input').val() == ""){
        $(this).addClass("no-value-input");
      }else{
        $(this).addClass("has-value-input");
      }
    }
  }
})(jQuery, Drupal, this, this.document);
