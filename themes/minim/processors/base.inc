<?php

/**
 * Implements hook_preprocess_html
 *
 * Adds typekit js to all pages
 */
function minim_preprocess_html(&$vars) {
  //drupal_set_message(print_r(get_class_methods($vars['page_object']), TRUE));
  //drupal_set_message(print_r($vars['page_object']->getMetaElements(), TRUE));
  $meta = $vars['page_object']->getMetaElements();
  foreach($meta as $metaController) {
    if ($metaController->getName() == 'viewport') {
       $metaController->setContent('width=device-width, initial-scale=1.0');
    }
  }
  $typekit = array(
    '#attached' => array(
      'js' => array(
        '//use.typekit.net/ita6dzs.js' => array('type' => 'external'),
        0 => array('data' => 'try{Typekit.load();}catch(e){}', 'type' => 'inline'), 
      ),
    ),
  );
  drupal_render($typekit);

  $searchbar = array(
    '#attached' => array(
      'js' => array(
        drupal_get_path('theme', 'minim') . '/js/search-bar.js',
      ),
    ),
  );
  drupal_render($searchbar);

$contact = array(
    '#attached' => array(
      'js' => array(
        drupal_get_path('theme', 'minim') . '/js/contact-form.js',
      ),
    ),
  );
  drupal_render($contact);

$tm = array(
    '#attached' => array(
      'js' => array(
        drupal_get_path('theme', 'minim') . '/js/tag-manager.js',
      ),
    ),
  );
  drupal_render($tm);


  //menu drop js for the hover menus
  $drop_menus = array(
    '#attached' => array(
      'library' => array(
        'minim/jquery.menu_drops',
      ),
      'js' => array(
        drupal_get_path('theme', 'minim') . '/js/menu-drops.js',
        drupal_get_path('theme', 'minim') . '/js/main-nav.js',
      ),
    ),
  );
  drupal_render($drop_menus);

  // Code to get menu for mobile menu here
  $menu_tree = \Drupal::service('menu_link.tree');
  $main_menu = $menu_tree->renderMenu('main');
  array_walk_recursive($main_menu, 'minim_change_theme_wrapper');
  // Get secondary menu
  $menu_tree = \Drupal::service('menu_link.tree');
  $secondary_menu = $menu_tree->renderMenu('secondary-navigation');
  array_walk_recursive($secondary_menu, 'minim_change_theme_wrapper');
  // Combine!
  $main_menu = array_merge($main_menu, $secondary_menu);
  // Mobile menus
  $mobile_menu = array(
    '#attached' => array(
      'library' => array(
        'minim/jquery.mmenu',
      ),
      'js' => array(
        drupal_get_path('theme', 'minim') . '/js/mmenu.js',
        array(
          'data' => array('mmenu' => drupal_render($main_menu)),
          'type' => 'setting'
        )
      ),
    ),
  );
  drupal_render($mobile_menu);
}

/**
 * Implements hook_preprocess_page
 *
 * General render array adjustments
 */
function minim_preprocess_page(&$vars) {
  //for some reason system main inserts itself into content region even if empty
  //so we remove it here to prevent bloat
  //to test if this is still applicable comment out, clear caches and look for a white space at
  //bottom of the front page
  if (count($vars['page']['content']) == 1 && empty($vars['page']['content']['system_main']['main']['#markup'])) {
    unset($vars['page']['content']);
  }

  //default styling for tabs
  if (!empty($vars['tabs'])) {
    foreach ($vars['tabs']['#primary'] as $tab_key => $tab) {
      $vars['tabs']['#primary'][$tab_key]['#link']['localized_options']['attributes']['class'][] = 'padding-xxs'; 
      $vars['tabs']['#primary'][$tab_key]['#link']['localized_options']['attributes']['class'][] = 'margin-s'; 
      $vars['tabs']['#primary'][$tab_key]['#link']['localized_options']['attributes']['class'][] = 'block-link'; 
      $vars['tabs']['#primary'][$tab_key]['#link']['localized_options']['attributes']['class'][] = 'bg-green'; 
    }
  }

  //node-type adjustments
  if (is_object($vars['node'])) {
    $node_type = $vars['node']->getType();
    switch ($node_type) {
      case 'google_form':
        //all the js and css specific to dealing with google forms
        minim_add_google_form_elements($vars);
      break;
      case 'portfolio_piece':
        //no titles on portfolio pages
        $vars['title'] = false;
      break;
      case 'facility':
        //automatically setting parent for facility nodes
        $menu_tree = \Drupal::service('menu_link.tree');
        $menu_tree->setPath('main', 'tools/facilities');
      break;
    }

    //set a variable here for nodes without bodies that
    //way we can hide titles as well.. allows for easy creation
    //of pages without content that we can place blocks on
    $body = $vars['node']->get('body')->getValue();
    if (empty($body[0]['value']) && $node_type != 'google_form') {
      $vars['page']['no_body'] = true;
    } 
  }
  if (\Drupal::request()->attributes->get('_system_path') == '2011-annual-report') {
    $drop_menus = array(
      '#attached' => array(
        'css' => array(
          drupal_get_path('theme', 'minim') . '/css/ar2011.css',
        ),
      ),
    );
    drupal_render($drop_menus);
  }
}

/**
 * Implements hook_preprocess_node
 *
 * Adds granular preprocess functions for nodes based on type
 *
 * @see processors/node.inc
 */
function minim_preprocess_node(&$vars) { 
  $type = $vars['node']->getType();
  if (!empty($type)) {
    $function = __FUNCTION__ . '_' . $type;
    if (function_exists($function)) {
      $function($vars, $hook);
    }
  }
}

/**
 * Implements hook_preprocess_block
 * 
 * Adds granular preprocess functions for blocks based on instance and plugin id
 * Plugin ID Example: minim_preprocess_block__pluginid
 * Instance Example: minim_preprocess_block_instance__instanceid
 *
 * @see minim/processors/blocks.inc
 */
function minim_preprocess_block(&$vars) {
  $sane_plugin_id = str_replace(':', '__', $vars['plugin_id']);
  $sane_plugin_id = str_replace('-', '_', $sane_plugin_id);
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $sane_plugin_id;
  $sub_functions[] = __FUNCTION__ . '_' . 'instance' . '__' . $vars['elements']['#contextual_links']['block']['route_parameters']['block'];

  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($vars);
    }
  }
}

/**
 * Implements hook_preprocess_field
 *
 * Adds granular preprocess functions for fields based on name
 *
 * @see minim/processors/fields.inc
 */
function minim_preprocess_field(&$vars) {
  $sub_functions[] = __FUNCTION__ . '__' . $vars['element']['#field_name'];
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($vars);
    }
  }
}

/**
 * Implements hook_preprocess_views_view_fields
 *
 * Adds granular preprocess functions for view fields
 *
 * @see minim/processors/views.inc
 */
function minim_preprocess_views_view_fields(&$variables) {
  $fields_rendered = '';
  if (!empty($variables['fields'])) {
    foreach ($variables['fields'] AS $id => $field) {
      if (!empty($field->separator)) {
        $fields_rendered .= $field->separator;
      }
      $fields_rendered .= $field->wrapper_prefix;
      $fields_rendered .= $field->label_html;
      $fields_rendered .= $field->content;
      $fields_rendered .= $field->wrapper_suffix;
    }
  }
  $variables['fields_rendered'] = $fields_rendered;

  // Allow for more granular preproces_functions
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->storage->id;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->storage->id . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

/**
 * Implements hook_preprocess_views_view
 *
 * Adds granular preprocess functions for views
 *
 * @see minim/processors/views.inc
 */
function minim_preprocess_views_view(&$variables) {
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->storage->id;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->storage->id . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

/**
 * Implements hook_preprocess_views_view
 *
 * Adds granular preprocess functions for unformatted view displays
 *
 * @see minim/processors/views.inc
 */
function minim_preprocess_views_view_unformatted(&$variables) {
  $sub_functions = array();
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->storage->id;
  $sub_functions[] = __FUNCTION__ . '__' . $variables['view']->storage->id . '__' . $variables['view']->current_display;
  foreach ($sub_functions AS $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }
}

/** start non-reusable helper functions **/
function minim_add_google_form_elements(&$vars) {
  $google_form = array(
    '#attached' => array(
      'js' => array(
        '//docs.google.com/static/forms/client/js/1232204844-formviewer_prd.js' => array('type' => 'external'),
        drupal_get_path('theme', 'minim') . '/js/google/h5f.min.js',
        1 => array(
          'data' => 'H5F.setup(document.getElementById(\'ss-form\'));_initFormViewer("[100,\x22#CCC\x22,[[[1739364875,[[2,102,,\x22\x22]\n]\n]\n]\n]\n]\n");', 
          'type' => 'inline',
          'scope' => 'footer',
        ), 
      ),
      'css' => array(
        '//docs.google.com/static/forms/client/css/212514800-mobile_formview_ltr.css' => array('type' => 'external'),
        drupal_get_path('theme', 'minim') . '/css/google-form.css',
      ),
    ),
  );
  drupal_render($google_form);
}
function minim_change_theme_wrapper(&$value, $key) {
  if ($key == '#theme_wrappers') {
    $value = array('menu_tree__mobile');
  }
}
/** end non-reusable helper functions **/
