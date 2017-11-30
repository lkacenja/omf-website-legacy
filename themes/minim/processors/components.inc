<?php
/**
 * @file
 * All custom component preprocess functions live here
 *
 * @see /minim/minim.theme
 */

function minim_menu_link__secondary(&$vars) {
  return '<span class="menu-divider"> / </span>'. theme_menu_link($vars);
}

/**
 * Adds classes to the main nav menu built by omf_blocks, as
 * well as organizes the different tiers to make it easier in template
 *
 * @see /modules/custom/omf_blocks/lib/Drupal/omf_blocks/Plugin/Block/LogoLinks.php
 * @see /minim/templates/components/omf_division_links.html.twig
 */
function minim_preprocess_omf_division_links(&$vars) {
  //hard coded to menu ids -- if the menu ids are changed
  //updates also need to be made to minim/js/menu-drop.js
  $services_id = 56;
  $education_id = 57;
  $tools_id = 58;

  $vars['division_links'] = array();
  foreach ($vars['tree'] as $key => $info) {
    if (is_numeric($key)) {
      $element = $info;

      $element['#localized_options']['set_active_class'] = TRUE;
      $vars['division_links'][$key]['title'] = $element['#title'];
      $vars['division_links'][$key]['link'] = l($element['#title'], $element['#href'], $element['#localized_options']);
      if (!empty($element['#localized_options']['attributes']['title'])) {
        $vars['division_links'][$key]['desc'] = $element['#localized_options']['attributes']['title'];
      }
      $vars['division_links'][$key]['class'] .= ' division-link-'. $key;
      if (!empty($element['#localized_options']['attributes']['class'][0])) {
        switch ($key) {
          case $services_id:
            $vars['division_links'][$key]['class'] .= ' bg-green';
          break;
          case $education_id:
            $vars['division_links'][$key]['class'] .= ' bg-red';
          break;
          case $tools_id:
            $vars['division_links'][$key]['class'] .= ' bg-orange';
          break;
        }
      }

      //organize second and tertiary items for template
      //lazy embedded foreach, could be improved later
      if (!empty($info['#below'])) {
        foreach ($info['#below'] as $subkey => $subinfo) {
          if (is_numeric($subkey)) {
            $vars['division_links'][$key]['sub'][$subkey]['title'] = $subinfo['#title'];
            $vars['division_links'][$key]['sub'][$subkey]['link'] = l($subinfo['#title'], $subinfo['#href'], $subinfo['#localized_options']);
          }
          if (!empty($subinfo['#below'])) {
            foreach ($subinfo['#below'] as $tertkey => $tertinfo) {
              if (is_numeric($tertkey)) {
                $vars['division_links'][$key]['sub'][$subkey]['tert'][$tertkey]['title'] = $tertinfo['#title'];
                $vars['division_links'][$key]['sub'][$subkey]['tert'][$tertkey]['link'] = l($tertinfo['#title'], $tertinfo['#href'], $tertinfo['#localized_options']);
              }
            }
          }
        }
      }
    }
  }
}

function minim_preprocess_omf_class_categories(&$vars) {
  foreach ($vars['categories'][0] as $key => $category) {
    $vars['category_info'][$key]['title'] = $category->taxonomy_term_data_name;
    $vars['category_info'][$key]['description'] = $category->description;
    $vars['category_info'][$key]['thumbnail'] = str_replace('public://', 'https://www.denveropenmedia.org/sites/default/files/', $category->image->uri);
    $vars['category_info'][$key]['link'] = '/education/class-types/' . $category->tid. '/' . minim_system_string($category->taxonomy_term_data_name);
  }
}

function minim_preprocess_omf_class_meta(&$vars) {
  foreach ($vars['classes'] as $key => $class) {
    $vars['classes'][$key]->url = '/education/classes/' . $class->nid .'/' . minim_system_string($class->node_title, '%2B');
    $vars['classes'][$key]->thumbnail = str_replace('public://', 'https://www.denveropenmedia.org/sites/default/files/', $class->image->uri);
    $vars['classes'][$key]->description = strip_tags($class->description);
    
    $alter = array(
      'max_length' => 200,
      'word_boundary' => true,
      'ellipsis' => true,
    );
    $vars['classes'][$key]->description = omf_scroll_trim_text($alter, $vars['classes'][$key]->description);
  }
}

function minim_system_string($string, $replacement = '_') {
  $string = trim($string);
  $string = str_replace(' ', $replacement, $string);
  $string = preg_replace('/[^a-z0-9-%-(^\")]+/', $replacement, strtolower($string));
  $string = str_replace('"', '%22', $string);
  return $string;
}

function minim_preprocess_omf_class(&$vars) {
  if (!empty($vars['class']) && count($vars['class']) > 0) {
    foreach ($vars['class']['dates'] as $product_key => $product_dates) {
      foreach ($product_dates as $key => $date) {
        $start = new DateTime($date['raw_date']->value, new DateTimeZone('UTC'));
        $start->setTimezone(new DateTimeZone('America/Denver'));
        $end = new DateTime($date['raw_date']->value2, new DateTimeZone('UTC'));
        $end->setTimezone(new DateTimeZone('America/Denver'));
        $human_start_date = $start->format('l, F j, Y');
        $human_end_date = $end->format('l, F j, Y');
        if($human_start_date == $human_end_date) {
          $vars['class']['human_dates'][$product_key][] = array(
            'date' => $human_start_date,
            'time' => $start->format(' g:ia').' - '.$end->format('g:ia'), 
            'path' => $date['path'],
          );
        }else{
          $vars['class']['human_dates'][$product_key][] = array(
            'date' => $human_start_date.' to '.$human_end_date,
            'time' => $start->format(' g:ia').' - '.$end->format('g:ia'), 
            'path' => $date['path'],
          );
        }
      }
    }
  }
}
