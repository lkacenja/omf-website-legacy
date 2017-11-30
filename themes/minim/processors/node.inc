<?php

function minim_preprocess_node_post(&$vars) {
  $vars['content'] = array('submitted' => array('#markup' => $vars['submitted'])) + $vars['content'];
  unset($vars['submitted']);
}

function minim_preprocess_node_portfolio_piece(&$vars) {
  // make it easier on twig, unset the video entirely if it is empty
  if (!empty($vars['content']['field_portfolio_video'][0])) {
    $vars['content']['video'] = $vars['content']['field_portfolio_video'][0]['#markup'];
  }
}

/**
 * Intercept the google form field and process it
 */ 
function minim_preprocess_node_google_form(&$vars) {
  if (!empty($vars['content']['field_google_form_live_form_url'][0]['#markup'])) {
    $vars['content']['google_form'] = minim_google_form_url_output($vars['content']['field_google_form_live_form_url'][0]['#markup']);
  }
}
