<?php
/**
 * @file
 * Contains \Drupal\omf_blocks\Plugin\Block\ClassCategories.
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
 *   id = "class_categories",
 *   admin_label = @Translation("Class Categories")
 * )
 */
class ClassCategories extends BlockBase {
  /**
   * Implements \Drupal\block\BlockBase::blockBuild().
   */
  public function build() {
    $this->configuration['label'] = t('Class Categories');
    $categories = $this->getClassCategories();
    return array(
      '#theme' => 'omf_class_categories',
      '#categories' => array(
        $categories, 
      ), 
    );
  }

  /**
   * Grabs class categories from the taxonomy on denveropenmedia.org and returns
   * it as an array.
   */
  public function getClassCategories() {
    $json = file_get_contents('http://www.denveropenmedia.org/services/class-categories.json');
    $categories = json_decode($json);
    return $categories;
  }
}
