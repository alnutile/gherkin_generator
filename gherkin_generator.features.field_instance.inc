<?php
/**
 * @file
 * gherkin_generator.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function gherkin_generator_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-gherkin_generator-field_tests'
  $field_instances['node-gherkin_generator-field_tests'] = array(
    'bundle' => 'gherkin_generator',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'example_node_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_tests',
    'label' => 'tests',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('tests');

  return $field_instances;
}
