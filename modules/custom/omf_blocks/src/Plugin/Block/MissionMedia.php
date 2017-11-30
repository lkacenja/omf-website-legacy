<?php
/**
 * @file
 * Contains \Drupal\omf_blocks\Plugin\Block\MissionMedia.
 */
namespace Drupal\omf_blocks\Plugin\Block;
use Drupal\block\BlockBase;
use Drupal\Component\Annotation\Plugin;
use Drupal\Core\Annotation\Translation;
use Drupal\Core\Session\AccountInterface;

/**
 * Mission Details Block appears on the front page.
 *
 * @Block(
 *   id = "mission_media",
 *   admin_label = @Translation("Mission Media")
 * )
 */
class MissionMedia extends BlockBase {
  /**
   * Implements \Drupal\block\BlockBase::blockBuild().
   */
  public function build() {
    $this->configuration['label'] = t('Mission Media');
    return array(
      '#theme' => 'omf_mission_media',
      '#tag_line' => t('Media with a Mission.'),
      '#mission' => t('Putting the power of the media and technology in the hands of the people.'),
      '#services' => array(
        'label' => t('Services'),
        'image_path' =>  'themes/minim/img/services-icon.png',
        'desc' => t('We help socially-conscious organizations use the power of media to carry out their mission and vision.'),
        'button_text' => t('Start a Project'),
        'link' => 'services/featured',
      ),
      '#education' => array(
        'label' => t('Education'),
        'image_path' =>  'themes/minim/img/education-icon.png',
        'desc' => t('We offer a variety of classes to help you create your own media and make it more effective.').'<br /><br />',
        'button_text' => t('Take a Class'),
        'link' => 'education/class-types',
      ),
      '#tools' => array(
        'label' => t('Tools'),
        'image_path' =>  'themes/minim/img/tools-icon.png',
        'desc' => t('We provide access to state-of-the-art media tools and high-end technology resources at affordable rates.'),
        'button_text' => t('Rent Equipment/Studios'),
        'link' => 'tools',
      ),
    );
  }
}
