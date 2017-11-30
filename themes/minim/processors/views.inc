<?php

function minim_preprocess_views_view__slides(&$vars) {
  $slider_attachments = array(
    '#attached' => array(
      'js' => array(
        drupal_get_path('theme', 'minim') . '/js/rotator.js' => array(),
      ),
      'css' => array(
        drupal_get_path('theme', 'minim') . '/css/slider.css' => array(),
      ),
      'library' => array(
        'minim/jquery.cycle',
      ),
    ),
  );
  drupal_render($slider_attachments);
}

function minim_preprocess_views_view_unformatted__slides(&$vars) {
  //row numbers were removed from core, add a tiny bit back in here
  $count = 0;
  $rows = $vars['rows'];
  foreach ($rows as $id => $row) {
    $count++;
    $vars['rows'][$id]['attributes']['class'][] = 'views-row-' . $count;
  }
}

/**
 * Implements hook_preprocess_views_view_fields__viewname
 * Adds classes for colors
 */
function minim_preprocess_views_view_fields__slides(&$vars) {
  switch($vars['view']->row_index) {
    case 0:
      $vars['colorclass'] = 'bg-green'; 
    break;
    case 1:
      $vars['colorclass'] = 'bg-red'; 
    break;
    case 2:
      $vars['colorclass'] = 'bg-orange'; 
    break;
  }
}

function minim_preprocess_views_view_unformatted__services_featured(&$vars) {
  minim_portfolio_listing($vars);
}
function minim_preprocess_views_view_unformatted__services_video(&$vars) {
  minim_portfolio_listing($vars);
}
function minim_preprocess_views_view_unformatted__services_web(&$vars) {
  minim_portfolio_listing($vars);
}
function minim_preprocess_views_view_unformatted__services_branding(&$vars) {
  minim_portfolio_listing($vars);
}
function minim_preprocess_views_view_unformatted__facilities(&$vars) {
  minim_portfolio_listing($vars);
}

function minim_portfolio_listing(&$vars) {
  $row_classes = array('padding-xxl', 'border-bottom-lgrey');
  foreach ($vars['rows'] as $key => $row) {
    $vars['rows'][$key]['attributes']['class'] = $row_classes;
  }
  minim_add_stripe_classes ($vars, $odd = array('bg-textured-light', 'bg-light-grey'));
}

function minim_preprocess_views_view_unformatted__people_staff(&$vars) {
  $row_classes = array();
  foreach ($vars['rows'] as $key => $row) {
    $vars['rows'][$key]['attributes']['class'] = $row_classes;
  }
  minim_add_stripe_classes ($vars, $odd = array('bg-textured-light', 'bg-light-grey'));
}
function minim_preprocess_views_view_unformatted__people_teachers(&$vars) {
  $row_classes = array();
  foreach ($vars['rows'] as $key => $row) {
    $vars['rows'][$key]['attributes']['class'] = $row_classes;
  }
  minim_add_stripe_classes ($vars, $odd = array('bg-textured-light', 'bg-light-grey'));
}
function minim_preprocess_views_view_unformatted__people_board(&$vars) {
  $row_classes = array();
  foreach ($vars['rows'] as $key => $row) {
    $vars['rows'][$key]['attributes']['class'] = $row_classes;
  }
  minim_add_stripe_classes ($vars, $odd = array('bg-textured-light', 'bg-light-grey'));
}
function minim_preprocess_views_view_unformatted__people_intern(&$vars) {
  $row_classes = array();
  foreach ($vars['rows'] as $key => $row) {
    $vars['rows'][$key]['attributes']['class'] = $row_classes;
  }
  minim_add_stripe_classes ($vars, $odd = array('bg-textured-light', 'bg-light-grey'));
}

function minim_add_stripe_classes (&$vars, $odd = array(), $even = array()) {
  foreach ($vars['rows'] as $key => $row) {
    if ($key % 2 == 0) {
      if (!empty($odd)) {
        foreach ($odd as $class_key => $class) {
          $vars['rows'][$key]['attributes']['class'][] = $class;
        }
      }
    }
    else {
      if (!empty($even)) {
        foreach ($even as $class_key => $class) {
          $vars['rows'][$key]['attributes']['class'][] = $class;
        } 
      }
    }
  }
}

function minim_preprocess_views_view_unformatted__portfolio_header(&$vars) {
  $vars['attributes']['class'][] = 'center-block';
}


function minim_preprocess_views_view_fields__portfolio_header(&$vars) {
  if (!empty($vars['fields']['field_portfolio_video']->content)) {
    $vars['fields']['field_portfolio_video']->content = strip_tags($vars['fields']['field_portfolio_video']->content);
  }
}

function minim_preprocess_views_view_unformatted__blog_page(&$vars) {
  $row_classes = array();
  foreach ($vars['rows'] as $key => $row) {
    $vars['rows'][$key]['attributes']['class'] = $row_classes;
  }
  minim_portfolio_listing($vars);
}

function minim_preprocess_views_view_fields__blog_page(&$vars) {
/*  foreach ($vars['fields']['field_post_tag'] as $key => $value){
    dsm($key);
  }
*/
  //dsm(get_class_methods($vars['row']->_entity)); 
  //dsm($vars['row']->_entity->get('field_post_tag')); 
  //$taxonomy_controller = $vars['row']->_entity->get('field_post_tag');
  //dsm(get_class_methods($taxonomy_controller)); 
  //dsm($taxonomy_controller->getValue());
}
