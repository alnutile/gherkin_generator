<?php
/**
 * @file
 * gherkin_generator.features.inc
 */

/**
 * Implements hook_node_info().
 */
function gherkin_generator_node_info() {
  $items = array(
    'gherkin_generator' => array(
      'name' => t('Gherkin Generator'),
      'base' => 'node_content',
      'description' => t('Generate Code in Guid'),
      'has_title' => '1',
      'title_label' => t('Name of Test'),
      'help' => '',
    ),
  );
  return $items;
}
