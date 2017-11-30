<?php
/**
 * @file
 * Contains \Drupal\omf_blocks\Plugin\Block\ContentBlock.
 */
namespace Drupal\omf_blocks\Plugin\Block;
use Drupal\block\BlockBase;
use Drupal\Component\Annotation\Plugin;
use Drupal\Core\Annotation\Translation;
use Drupal\Core\Session\AccountInterface;

/**
 * Logo + Division Link block that appears in the header on every page. 
 *
 * @Block(
 *   id = "logo_links",
 *   admin_label = @Translation("Logo Links")
 * )
 */
class LogoLinks extends BlockBase {
  /**
   * Implements \Drupal\block\BlockBase::blockBuild().
   */
  public function build() {
    $this->configuration['label'] = t('Logo & Links');

    // Grab the main menu to generate division links
    $menu_tree = \Drupal::service('menu_link.tree');
    $main_menu = $menu_tree->renderMenu('main');

    // Get the logo from the theme
    $logo = theme_get_setting('logo');
    $logo = array(
      '#theme' => 'omf_logo',
      '#image_url' => $logo['url'],
      '#front_url' => url(),
    );
    
    return array(
      'logo' => $logo,
      'menu' => $main_menu,
    );
  }
}
