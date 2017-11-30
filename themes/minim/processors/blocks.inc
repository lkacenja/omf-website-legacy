<?php
/**
 * @file
 * All block level preprocess functions live here
 *
 * @see /minim/processors/base.inc
 */

function minim_preprocess_block__omfooter (&$vars) {
  $vars['attributes']['class'][] = 'bg-grey bg-textured padding-m-vert';
  $vars['attributes']['class'][] = 'clearfix';
}

function minim_preprocess_block__search_form_block (&$vars) {
  $vars['attributes']['class'][] = 'bg-textured-light bg-light-grey padding-s';
}

function minim_preprocess_block__class_categories (&$vars) {
  $vars['attributes']['class'][] = 'clearfix';
  $vars['content_attributes']['class'][] = 'center-block';
}

function minim_preprocess_block__views_block__slides_block_1 (&$vars) {
  $vars['attributes']['class'][] = 'fit-image';
}

function minim_preprocess_block_instance__logolinks (&$vars) {
  //sets a class on the main navigation for the active area
  $area_set = false;
  foreach ($vars['content']['menu'] as $id => $link) {
    if (!empty($link['#attributes'])) {
      foreach ($link['#attributes']['class'] as $key => $class) {
        if ($class == 'active-trail') {
          $area_set = true;
          $vars['attributes']['class'][] = 'area-'.$id;
        }
      } 
    }
  }
  if (!$area_set && !drupal_is_front_page()) {
    $vars['attributes']['class'][] = 'area-general';
  }

  $vars['attributes']['class'][] = 'clearfix';
  $vars['content_attributes']['class'][] = 'center-block';
}

function minim_preprocess_block_instance__secondarynavigation (&$vars) {
  $vars['attributes']['class'][] = 'bg-grey';
  $vars['attributes']['class'][] = 'horizontal-nav';
  $vars['attributes']['class'][] = 'clearfix';

  $vars['content_attributes']['class'][] = 'center-block';
  $vars['content_attributes']['class'][] = 'text-s';
  $vars['content_attributes']['class'][] = 'uppercase';

  //adds button styles to secondary nav links
  foreach ($vars['content'] as $key => $info) {
    if (is_numeric($key)) {
      $vars['content'][$key]['#localized_options']['attributes']['class'][] = 'padding-xs';
      $vars['content'][$key]['#localized_options']['attributes']['class'][] = 'block-link';
      unset($vars['content'][$key]['#below']);
    }
  }
}

/**
 * Utility function for styling custom image blocks
 *
 * @todo blocks defined in the custom block interface do not
 * seem to have a general id that can be targetted thus the string of
 * specific functions below. For now we have to declare the preprocess for
 * each one manually.
 */
function minim_image_block (&$vars) {
  $vars['attributes']['class'][] = 'relative';
  $vars['attributes']['class'][] = 'bg-green';
}
function minim_preprocess_block_instance__services (&$vars) { minim_image_block($vars); }
function minim_preprocess_block_instance__servicesvideo (&$vars) { minim_image_block($vars); }
function minim_preprocess_block_instance__serviceseducation (&$vars) { minim_image_block($vars); }
function minim_preprocess_block_instance__servicestools (&$vars) { minim_image_block($vars); }

/**
 * Adds classes to the menu items provided by the submenu block
 *
 * @see /modules/custom/omf_blocks/lib/Drupal/omf_blocks/Plugin/Block/SubMenu.php
 */
function minim_submenu_classes(&$menu) {
  if (!empty($menu)) {
    foreach ($menu as $key => $info) {
      if (is_numeric($key)) {
        $menu[$key]['#attributes']['class'][] = 'margin-s';
        $menu[$key]['#attributes']['class'][] = 'round-corners';
        $menu[$key]['#localized_options']['attributes']['class'][] = 'block-link';
        
        //d8 seems to be creating duplicate classes, so we strip them out here
        if (!empty($menu[$key]['#localized_options']['attributes']['class'])) {
          $menu[$key]['#localized_options']['attributes']['class'] = array_unique($menu[$key]['#localized_options']['attributes']['class']);
        }

        //tertiary nav menu items off of the main nav
        if (in_array('sub', $menu[$key]['#localized_options']['attributes']['class'])) {
          $menu[$key]['#attributes']['class'][] = 'text-xs';
          $menu[$key]['#attributes']['class'][] = 'inline';
          $menu[$key]['#attributes']['class'][] = 'red';
          $menu[$key]['#theme'] = 'menu_link__secondary';
        }
        //red background for tertiary nav link back
        elseif (in_array('active-trail', $menu[$key]['#localized_options']['attributes']['class'])) {
          $menu[$key]['#attributes']['class'][] = 'bg-red';
        }
        //tertiary nav link back and back 
        if (!in_array('sub', $menu[$key]['#localized_options']['attributes']['class'])) {
          $menu[$key]['#localized_options']['attributes']['class'][] = 'padding-xs';
        }
      }
    }
  }
}

function minim_preprocess_block_instance__submenu (&$vars) {
  $vars['attributes']['class'][] = 'clearfix';
  $vars['attributes']['class'][] = 'border-bottom-grey';
  $vars['content_attributes']['class'][] = 'center-block';

  minim_submenu_classes($vars['content']['tertiary_menu']);
  minim_submenu_classes($vars['content']['secondary_menu']);
}

function minim_preprocess_block_instance__views_block__posts_block_1 (&$vars) {
  $vars['attributes']['class'][] = 'bg-green';
  $vars['attributes']['class'][] = 'padding-xl';
  $vars['content_attributes']['class'][] = 'clearfix';
  minim_dash_block ($vars);
}

function minim_preprocess_block__views_block__testimonials_block_1 (&$vars) {
  $vars['attributes']['class'][] = 'bg-green';
  $vars['attributes']['class'][] = 'padding-xl';
  $vars['content_attributes']['class'][] = 'align-center';
  $vars['content_attributes']['class'][] = 'clearfix';
  minim_dash_block ($vars);
}
function minim_preprocess_block__views_block__testimonials_block_2 (&$vars) {
  $vars['attributes']['class'][] = 'bg-green';
  $vars['attributes']['class'][] = 'padding-xl';
  $vars['content_attributes']['class'][] = 'align-center';
  $vars['content_attributes']['class'][] = 'clearfix';
  minim_dash_block ($vars);
}

/**
 * Adds a dash to right and left of title, for example see posts
 * block on front page
 */
function minim_dash_block (&$vars) {
  $vars['attributes']['class'][] = 'clearfix';
  $vars['content_attributes']['class'][] = 'center-block';
  $vars['label'] = '<div class="dash-left inline bg-white">&nbsp;</div>'. $vars['label'];
  $vars['label'] .= '<div class="dash-right inline bg-white">&nbsp;</div>';
}

function minim_preprocess_block_instance__missionmedia (&$vars) {
  $vars['attributes']['class'][] = 'clearfix';
  $vars['attributes']['class'][] = 'padding-l-vert';
  $vars['attributes']['class'][] = 'align-center';
  $vars['content_attributes']['class'][] = 'center-block';
}

function minim_preprocess_block_instance__toolswebtv (&$vars) {
  $vars['attributes']['class'][] = 'clearfix';
  $vars['attributes']['class'][] = 'padding-l-vert';
  $vars['content_attributes']['class'][] = 'center-block';
}

function minim_preprocess_block__views_block__page_image_block_1 (&$vars) {
  $vars['attributes']['class'][] = 'fit-image';
}

function minim_preprocess_block__views_block__portfolio_header_block_1 (&$vars) {
  $vars['attributes']['class'][] = 'bg-textured-light bg-light-grey';
  $vars['content_attributes']['class'][] = 'center-block';
}

function minim_preprocess_block_instance__toolsvideoproduction (&$vars) {
  minim_preprocess_horizontal_feature ($vars);
}

function minim_preprocess_block_instance__toolsfacilities (&$vars) {
  minim_preprocess_horizontal_feature ($vars);
}

function minim_preprocess_horizontal_feature (&$vars) {
  $vars['attributes']['class'][] = 'clearfix';
  $vars['attributes']['class'][] = 'bg-textured-light bg-light-grey';
  $vars['content_attributes']['class'][] = 'center-block';
}
