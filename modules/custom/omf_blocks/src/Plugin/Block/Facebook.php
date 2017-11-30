<?php
/**
 * @file
 * Contains \Drupal\omf_blocks\Plugin\Block\Facebook.
 */
namespace Drupal\omf_blocks\Plugin\Block;
use Drupal\block\BlockBase;
use Drupal\Component\Annotation\Plugin;
use Drupal\Core\Annotation\Translation;
use Drupal\Core\Session\AccountInterface;

/**
 * Block containing OMF Class categories pulled from denveropenmedia.org 
 *
 * @Block(
 *   id = "face_book",
 *   admin_label = @Translation("Face Book")
 * )
 */
class Facebook extends BlockBase {
  /**
   * Implements \Drupal\block\BlockBase::blockBuild().
   */
  public function build() {
    $this->configuration['label'] = t('Face book');
    //$categories = $this->getClassCategories();

    return array(
      '#markup' => '<div data-href="https://www.facebook.com/Open-Media-Foundation-209082215492/?ref=bookmarks" data-small-header="false" data-adapt-container-width="true" data-hide-cover="false" data-show-facepile="true" data-show-posts="true" class="fb-page fb_iframe_widget" fb-xfbml-state="rendered" fb-iframe-plugin-query="adapt_container_width=true&amp;app_id=113869198637480&amp;container_width=588&amp;hide_cover=false&amp;href=https%3A%2F%2Fwww.facebook.com%2FOpen-Media-Foundation-209082215492%2F%3Fref%3Dbookmarks&amp;locale=en_US&amp;sdk=joey&amp;show_facepile=true&amp;show_posts=true&amp;small_header=false"><span style="vertical-align: bottom; width: 340px; height: 500px;"><iframe name="f284f0e618" width="1000px" height="1000px" frameborder="0" allowtransparency="true" allowfullscreen="true" scrolling="no" title="fb:page Facebook Social Plugin" src="https://www.facebook.com/v2.5/plugins/page.php?adapt_container_width=true&amp;app_id=113869198637480&amp;channel=https%3A%2F%2Fs-static.ak.facebook.com%2Fconnect%2Fxd_arbiter%2FwjDNIDNrTQG.js%3Fversion%3D41%23cb%3Df33b865a98%26domain%3Ddevelopers.facebook.com%26origin%3Dhttps%253A%252F%252Fdevelopers.facebook.com%252Ff3d841993c%26relation%3Dparent.parent&amp;container_width=588&amp;hide_cover=false&amp;href=https%3A%2F%2Fwww.facebook.com%2FOpen-Media-Foundation-209082215492%2F%3Fref%3Dbookmarks&amp;locale=en_US&amp;sdk=joey&amp;show_facepile=true&amp;show_posts=true&amp;small_header=false" style="border: none; visibility: visible; width: 340px; height: 500px;" class=""></iframe></span></div>',
    );
  }

  /**
   * Grabs class categories from the taxonomy on denveropenmedia.org and returns
   * it as an array.
   */
}
