<?php

function s1_load_get_ajax($entity_type, $id, $view_mode) {
  $entities = entity_load($entity_type, [$id]);
  $view = entity_view($entity_type, $entities, $view_mode);
  return $view;
}

function s1_load_ajax_callback($page_callback_result) {
  $content = is_string($page_callback_result) ? $page_callback_result : drupal_render($page_callback_result);
  print $content;
  drupal_page_footer();
}