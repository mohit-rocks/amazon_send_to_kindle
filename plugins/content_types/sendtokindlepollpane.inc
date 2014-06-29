<?php

/**
 * @file
 * Creating a custom content pane which renders a poll into a pane.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Send to Kindle Poll Pane'),
  'description' => t('Displays the send to kidle button on the page.'),
  'single' => TRUE,
  'content_types' => array('sendtokindlepane'),
  'render callback' => 'send_to_kindle_pane_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'defaults' => array(),
  'category' => array(t('Node'), -9),
);

/**
 * Run-time rendering of the body of the block.
 *
 * @param $subtype
 * @param $conf
 *   Configuration as done at admin time.
 * @param $args
 * @param $context
 *   Context
 *
 * @return
 *   An object with at least title and content members.
 */
function send_to_kindle_pane_render($subtype, $conf, $args, $context) {

  $node = isset($context->data) ? $context->data : NULL;
  $content_types = variable_get('amazon_send_to_kindle_nodes', array());
  $node_types = variable_get('amazon_send_to_kindle_node_type', 'full');

  // Include the javascript file provided by the Amazon.
  $module_path = drupal_get_path('module', 'amazon_send_to_kindle');
  drupal_add_js($module_path . '/amazon_send_to_kindle.js', 'file');
  drupal_add_css($module_path . '/kindle.css');

  if ($content_types[$node->type] != NULL && ($node_types == $view_mode || $node_types == 'both')) {
    $url = url(drupal_lookup_path('alias', 'node/' . $node->nid), array('absolute' => TRUE));
    if (!$url) {
      $url = url('node/' . $node->nid, array('absolute' => TRUE));
    }
    // Append the HTML given by the Amazon here.
    // We are fetching from the text area variable which we stored during module
    // configuration.
    // Assign the HTML with the node render content.
    if (variable_get('amazon_send_to_kindle_button_type', 0) == 0) {
      $output = variable_get('amazon_send_to_kindle_html', NULL);
    }
    else {
      $output = _amazon_send_to_kindle_get_html($module_path);
    }
    $block = new stdClass();
    $block->title = t('Send to Kindle');
    $block->content = array('#markup' => $output);
    return $block;
  }
}
