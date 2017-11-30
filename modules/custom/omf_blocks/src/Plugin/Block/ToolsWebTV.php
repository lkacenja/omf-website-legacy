<?php
/**
 * @file
 * Contains \Drupal\omf_blocks\Plugin\Block\ToolsWebTV.
 */
namespace Drupal\omf_blocks\Plugin\Block;
use Drupal\block\BlockBase;
use Drupal\Component\Annotation\Plugin;
use Drupal\Core\Annotation\Translation;
use Drupal\Core\Session\AccountInterface;

/**
 * Tools Web TV Block for Tools landing page
 *
 * @Block(
 *   id = "tools_webtv",
 *   admin_label = @Translation("Tools Web TV")
 * )
 */
class ToolsWebTV extends BlockBase {
  /**
   * Implements \Drupal\block\BlockBase::blockBuild().
   */
  public function build() {
    $this->configuration['label'] = t('Tools: WebTV');
    return array(
      '#theme' => 'omf_tools_webtv',
      '#title' => t('Web/TV Distribution'),
      '#dom' => array(
        'label' => t('Denver Open Media Public Access TV Station'),
        'image_path' =>  'themes/minim/img/dom-tools.png',
        'desc' => t("OMF oversees Denver's public access TV station, Denver Open Media, the only user-driven TV station in the country where viewers decide what's on. All video submitted to DOM are shown on Comcast Channels 56, 57 and 219, and also available at denveropenmedia.org. Individuals working on non-commercial projects can get free access to the same tools offered by OMF through DOM's membership program."),
        'link' => '/tools/denver-open-media',
      ),
      '#cochannel' => array(
        'label' => t('Colorado Channel - Live & Repeat Coverage of the State Legislature'),
        'image_path' =>  'themes/minim/img/cochannel-tools.png',
        'desc' => t("OMF works with the Colorado State Legislature to broadcast every floor session of the Colorado State Senate and House of Representatives, live online and on Comcast Channel 165. Together, we are increasing participation and transparency in government."),
        'link' => 'http://www.coloradochannel.net',
      ),
      '#omp' => array(
        'label' => t('Open Media Project'),
        'image_path' =>  'themes/minim/img/omp-tools.png',
        'desc' => t("OMF is leading a nation-wide effort to give communities more control over community media. We are working with organizations across the country to create a network of user-driven media centers, collaborating on the creation of open-source software that helps to modernize and streamline operations, while increasing civic engagement through new media."),
        'link' => '/tools/open-media-project',
      ),
    );
  }
}
