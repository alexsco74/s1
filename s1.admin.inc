<?php

function s1_admin_config_form() {
  $form = [];
  $form['view_mode'] = [
    '#type' => 'html_tag',
    '#tag' => 'h2',
    '#value' => t('Use scroll entity loader for view modes'),
  ];

  $entity_info = entity_get_info();
  foreach ($entity_info as $entity_type => $entity_info_ar) {
    $view_modes = $entity_info_ar['view modes'];
    $form[$entity_type] = [
      '#type' => 'fieldset',
      '#title' => $entity_info_ar['label'],
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    ];
    foreach ($entity_info_ar['bundles'] as $bundle => $bundle_ar) {
      $form[$entity_type][$bundle] = [
        '#type' => 'fieldset',
        '#title' => $bundle_ar['label'],
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      ];
      foreach ($view_modes as $view_mode_key => $view_mode_ar) {
        $variable_key = 's1_view_mode__' . $entity_type . '__' . $bundle . '__' . $view_mode_key;
        $form[$entity_type][$bundle][$variable_key] = [
          '#type' => 'checkbox',
          '#title' => $view_mode_ar['label'],
          '#default_value' => variable_get($variable_key, FALSE),
        ];
      }
    }
  }
  return system_settings_form($form);
}