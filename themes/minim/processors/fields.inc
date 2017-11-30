<?php

function minim_preprocess_field__field_block_caption(&$vars) {
  $vars['attributes']['class'][] = 'absolute-center';
  $vars['attributes']['class'][] = 'align-center';
}

function minim_preprocess_field__field_block_image(&$vars) {
  $vars['attributes']['class'][] = 'fit-image';
}

function minim_preprocess_field__field_feature_title(&$vars) {
  $vars['attributes']['class'][] = 'text-xl padding-m-vert red';
}

function minim_preprocess_field__field_feature_link(&$vars) {
  $vars['attributes']['class'][] = 'bg-red float-left';
  $vars['items'][0]['#options']['attributes']['class'][] = 'text-xs padding-xs block-link';
}

/**
 * Horizontal Feature Block Image
 */
function minim_preprocess_field__field_feature_image(&$vars) {
  $vars['attributes']['class'][] = 'float-left block-link';
}
