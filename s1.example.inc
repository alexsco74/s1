<?php

function s1_example() {
  $build['title'] = [
    '#markup' => '<h2>' . 'Entity list teaser' . '</h2>',
  ];
  $build['filter'] = drupal_get_form('s1_example_form');
  if (empty($_GET['entity'])) {
    $build['content'] = [
      '#markup' => t('Please select entity bundle for view'),
    ];
    return $build;
  }
  $entity = explode('__', $_GET['entity']);
  $entity_type = array_shift($entity);
  $bundle = array_shift($entity);
  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', $entity_type)
    ->entityCondition('bundle', [$bundle])
    ->pager();
  if ($entity_type == 'node') {
    $query->addTag('node_access');
  }
  $result = $query->execute();
  if (empty($result[$entity_type])) {
    $build['content'] = [
      '#markup' => t('Entity not found.'),
    ];
    return $build;
  }
  $ids = array_keys($result[$entity_type]);
  $entities = entity_load($entity_type, $ids);
  $view = entity_view($entity_type, $entities, 'teaser');
  $build['content'] = $view;
  $build['pager'] = [
    '#theme' => 'pager',
  ];
  return $build;
}

function s1_example_form($form, &$form_state) {
  $options = [];
  $entity_info = entity_get_info();
  foreach ($entity_info as $entity_type => $entity_info_ar) {
    if ($entity_type == 'comment') {
      continue;
    }
    $options[$entity_info_ar['label']] = [];
    foreach ($entity_info_ar['bundles'] as $bundle => $bundle_ar) {
      $options[$entity_info_ar['label']][$entity_type . '__' . $bundle] = $bundle_ar['label'];
    }
  }
  $form['entity'] = [
    '#type' => 'select',
    '#title' => t('Entity + bundle'),
    '#options' => $options,
  ];
  if (!empty($_GET['entity'])) {
    $form['entity']['#default_value'] = $_GET['entity'];
  }
  $form['filter'] = [
    '#type' => 'submit',
    '#value' => t('Submit'),
  ];
  return $form;
}

function s1_example_form_submit($form, &$form_state) {
  if (empty($form_state['values']['entity'])) {
    return TRUE;
  }
  $entity = filter_xss($form_state['values']['entity'], []);
  if (empty($entity)) {
    return TRUE;
  }
  $form_state['redirect'] = [
    $_GET['q'],
    [
      'query' =>
        ['entity' => $entity],
    ],
  ];
}