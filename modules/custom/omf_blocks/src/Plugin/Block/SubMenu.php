<?php
/**
 * @file
 * Contains \Drupal\omf_blocks\Plugin\Block\SubMenu.
 */
namespace Drupal\omf_blocks\Plugin\Block;
use Drupal\block\BlockBase;
use Drupal\Component\Annotation\Plugin;
use Drupal\Core\Annotation\Translation;
use Drupal\Core\Session\AccountInterface;

/**
 * Content Block
 *
 * @Block(
 *   id = "sub_menu",
 *   admin_label = @Translation("Sub Menu")
 * )
 */
class SubMenu extends BlockBase {
  /**
   * Implements \Drupal\block\BlockBase::blockBuild().
   */
  public function build() {
    $this->configuration['label'] = t('Secondary Menu Bar');
    $secondary_menus = $this->getSecondaryMenu();
    if (!empty($secondary_menus)) {
      $secondary_menus['secondary']['#theme_wrappers'][0] = 'menu_tree__secondary';
    
      // Two different sets of markup -- one for navigating tertiary items, the
      // other for top level secondary items
      if (!empty($secondary_menus['tertiary'])) {
        $secondary_menus['tertiary']['#theme_wrappers'][0] = 'menu_tree__back';
        return array(
          'tertiary_prefix' => array('#markup' => '<div class="back-menu horizontal-nav">'),
          'tertiary_menu' => $secondary_menus['tertiary'],
          'tertiary_suffix' => array('#markup' => '</div>'),
          'secondary_prefix' => array('#markup' => '<div class="secondary-menu">'), 
          'secondary_menu' => $secondary_menus['secondary'], 
          'secondary_suffix' => array('#markup' => '</div>'),
        );
      }
      else {
        return array(
          'prefix' => array('#markup' => '<div class="horizontal-nav">'),
          'secondary_menu' => $secondary_menus['secondary'], 
          'suffix' => array('#markup' => '</div>'),
        );
      }
    }
  }

  /**
   * Generates an array with render arrays for secondary and tertiary menu items
   * beneath the current active menu item
   */
  private function getSecondaryMenu() {
    // Get the current menu trail to use for our sub menu
    $trail = omf_blocks_menu_get_active_trail();
    foreach ($trail as $key => $info) {
      if (!empty($info['menu_name'])) {
        $menu_name = $info['menu_name'];
        break;
      }
    }
    if (empty($menu_name)) {
      return false;
    }

    // Get the render array for this menu
    $menu_tree = \Drupal::service('menu_link.tree');
    $menu = $menu_tree->buildPageData($menu_name);

    // Clone it so that we can make modifications
    $menu_clone = $menu;

    $menu_exists = false; // By default we assume the active menu item has no sub items
    $deeper = true; // True until we get to the last active tier with children
    $tier = 0; // Current depth within the menu

    // Loops through menu tiers until we get to the last
    // active tier with children
    while ($deeper == true) {
      $tier++;
      $deeper = false; // Assume there are no more active tiers

      // Store first item of each menu tier for later use
      $previous_first_value = reset($menu_clone);
      $previous_first_key = key($menu_clone);
      $trail[$tier] = array($previous_first_key => $previous_first_value);

      // Check each menu item to see if it is in the active trail and has children
      // that are not set to disabled in the menu administration 
      foreach ($menu_clone as $primary_key => $primary_info) {
        // Is the item in the active trail and has a sub menu
        if (!empty($primary_info['below']) && $primary_info['link']['in_active_trail']) {
          // Check to see if at least one of the sub menu items is not disabled
          foreach ($primary_info['below'] as $sub_key => $sub_info) {
            if (!$sub_info['link']['hidden']) {
              // All checks past, set the children of this menu item as the current
              // sub menu candidate
              $last_parent = array($primary_key => $primary_info);
              $menu_clone = $primary_info['below'];
              $deeper = true; // We need to check this new sub menu for active items
              $menu_exists = true; // At this point we know there is a sub menu to be displayed
            }
          }
        }
      }
    }

    if ($menu_exists) {
      // Get rid of any children at this point as we only display 1 level
      foreach ($menu_clone as $menu_id => $menu_item) {
        $menu_clone[$menu_id]['below'] = array();
      }

      // If we are deeper then 2 levels we wrap the sub-sub menu in a separate class
      // and also add a specific class for sub-sub active links
      if ($tier > 2) {
        foreach ($menu_clone as $menu_id => $menu_item) {
          $menu_item['link']->localized_options['attributes']['class'][] = 'sub';
          if (!empty($menu_item['link']->localized_options['attributes']['class'])) {
            $menu_item['link']->localized_options['attributes']['class'] = array_unique($menu_item['link']->localized_options['attributes']['class']);
            foreach ($menu_item['link']->localized_options['attributes']['class'] as $ckey => $class) {
              if ($class == 'active-trail') {
                $menu_item['link']->localized_options['attributes']['class'][] = 'sub-active-trail';
              }
            }
          }
        }
        
        // Construct the second menu with back button and current area
        $tertiary = array();

        // Add the parent menu item of these children to the beginning of the menu
        // array for display as the active parent
        reset($last_parent);
        $last_parent[key($last_parent)]['below'] = '';
        $last_parent[key($last_parent)]['link']->localized_options['attributes']['class'][] = 'parent-link';
        $tertiary = array_merge($last_parent, $tertiary);

        // Add the first menu item from the parent menu to the menu array allowing user to go back up a level
        reset($trail[$tier-1]);
        $trail[$tier-1][key($trail[$tier-1])]['link']->title = '<< Up';
        $trail[$tier-1][key($trail[$tier-1])]['link']->localized_options['attributes']['class'][] = 'back-link';
        $tertiary = array_merge($trail[$tier-1], $tertiary);
      }
      // Add the final secondary menu to the render array
      if (!empty($menu_clone)) {
        $menus['secondary'] = $menu_tree->renderTree($menu_clone);
      }
      // Add the final tertiary menu to the render array
      if (!empty($tertiary)) {
        $menus['tertiary'] = $menu_tree->renderTree($tertiary);
      }
      return $menus;
    }
    else {
      return false;
    }
  }

  /**
   * Implements \Drupal\block\BlockBase::access().
   */
  public function access(AccountInterface $account) {
    //todo: there must be a way to not do this check twice...
    $secondary_menu = $this->getSecondaryMenu();
    if (empty($secondary_menu)) {
      return false;
    }
    return $account->hasPermission('access content');
  }
}
