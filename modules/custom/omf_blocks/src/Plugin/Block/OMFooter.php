<?php
/**
 * @file
 * Contains \Drupal\omf_blocks\Plugin\Block\Footer.
 */
namespace Drupal\omf_blocks\Plugin\Block;
use Drupal\block\BlockBase;
use Drupal\Component\Annotation\Plugin;
use Drupal\Core\Annotation\Translation;
use Drupal\Core\Session\AccountInterface;

/**
 * Footer informational block.
 *
 * @Block(
 *   id = "OMFooter",
 *   admin_label = @Translation("OMFooter")
 * )
 */
class OMFooter extends BlockBase {
  /**
   * Implements \Drupal\block\BlockBase::blockBuild().
   */
  public function build() {
    $this->configuration['label'] = t('Footer');
    return array(
      '#theme' => 'omf_footer',
      '#contact' => array(
        'label' => t('Contact Us'),
        'phone' => t('720-222-0159'),
        'fax' => t('303-534-5098'),
        'contact_link' => l('Contact Us', 'contact'),
        'address' => '<a href="https://www.google.com/maps/place/700+Kalamath+St/@39.727578,-104.99978,327m/data=!3m1!1e3!4m2!3m1!1s0x876c7f3067232105:0xa007f513de4d7e33?hl=en">700 Kalamath St | Denver, CO 80204</a>',
      ),
      '#connect' => array(
        'label' => t('Connect'),
        'fb_url' => 'http://www.facebook.com/#!/pages/Open-Media-Foundation/209082215492?ref=ts',
        'fb_icon' => '/themes/minim/img/facebook-icon.png',
        'twitter_url' => 'http://twitter.com/OMFoundation',
        'twitter_icon' => '/themes/minim/img/twitter-icon.png',
        'youtube_url' => 'http://www.youtube.com/OpenMediaFoundation',
        'youtube_icon' => '/themes/minim/img/youtube-icon.png',
        'newsletter_label' => t('Sign up for our newsletter'),
        'newsletter_form' => '<form name="ccoptin" action="http://visitor.constantcontact.com/d.jsp" target="_blank" method="post"/><input type="text" class="updates" name="ea" size="20" value="email"/><input type="submit" name="go" value="GO" class="submit"  /><input type="hidden" name="m" value="1101845959534"><input type="hidden" name="p" value="oi"></form>',
        ),
      '#other' => array(
        'disclaimer' => t('The Open Media Foundation is a not-for-profit, 501(C)(3) corporation'),
      ),
    );
  }
}
