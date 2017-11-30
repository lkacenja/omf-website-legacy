<?php

namespace Drupal\omf_scroll\Controller;

class omfScroll {
  /** 
   * Provides a blank page to attach blocks to for paths like
   * the home page and tools
   */ 
  public function scrollPage() {
    return false;
  }

  /**
   * Provides an array of classes available in a given category pulled from denveropenmedia.org
   * used to generate pages like education/class-types/769/video_production
   */  
  public function classCategoryPage($category_id, $category_name) {
    $json = file_get_contents('http://www.denveropenmedia.org/services/class-meta?tid='. $category_id);
    $classes = json_decode($json);
    $classes = array_reverse($classes);
    $content = array(
      '#theme' => 'omf_class_meta',
      '#classes' => $classes,
    );
    
    //set path for all class category pages to education
    $menu_tree = \Drupal::service('menu_link.tree');
    $menu_tree->setPath('main', 'education/class-types');
    return $content;
  }

  /**
   * Provides an array of information on a specific class pulled from denveropenmedia.org
   */
  public function classPage($class_id, $class_name) {
    // Unfortunately the only way to get class meta and the associated product is
    // via two services callbacks that we combine
    $meta_url = 'http://www.denveropenmedia.org/services/class-display.json?nid='.$class_id;
    $product_url = 'http://www.denveropenmedia.org/services/classes.json?title='.$class_name;
    $product_json = file_get_contents($product_url);
    $meta_json = file_get_contents($meta_url);
    $product = json_decode($product_json);
    $meta = json_decode($meta_json);
    $class = array();

    // Assemble the metadata and product information into something useful
    // for the theme function
    $class['title'] = $meta[0]->node_title;
    $class['description'] = $meta[0]->Description;
    if (!empty($product[0]->image->uri)) {
      $class['image'] = str_replace('public://', 'http://www.denveropenmedia.org/sites/default/files/', $product[0]->image->uri); 
    }
    if (!empty($product[0]->price)) {
      $class['price'] = $product[0]->price;
    }
    if (!empty($product[0]->member_price)) {
      $class['member_price'] = $product[0]->member_price;
    }
    if (!empty($meta[0]->required_certs)) {
      $class['required_certs'] = $meta[0]->required_certs;
    }
    if (!empty($meta[0]->earned_certs)) {
      $class['earned_certs'] = $meta[0]->earned_certs;
    }

    // Add all of the class dates
    foreach ($product as $key => $info) {
      foreach ($info->field_class_date as $instance_key => $instance) {
        $class['dates'][$key][] = array(
          'path' => 'node/'. $info->nid,
          'raw_date' => $instance,
        );
      }
    }

    $content = array(
      '#theme' => 'omf_class',
      '#class' => $class,
    );

    //set class page menu paths to to education
    $menu_tree = \Drupal::service('menu_link.tree');
    $menu_tree->setPath('main', 'education/class-types');

    return $content;
  }
}
