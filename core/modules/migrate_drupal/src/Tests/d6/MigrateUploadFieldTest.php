<?php

/**
 * @file
 * Contains \Drupal\migrate_drupal\Tests\d6\MigrateUploadInstanceTest.
 */

namespace Drupal\migrate_drupal\Tests\d6;

use Drupal\migrate\MigrateExecutable;
use Drupal\migrate_drupal\Tests\MigrateDrupalTestBase;

/**
 * Tests the Drupal 6 upload settings to Drupal 8 field migration.
 */
class MigrateUploadFieldTest extends MigrateDrupalTestBase {

  /**
   * The modules to be enabled during the test.
   *
   * @var array
   */
  static $modules = array('file', 'node');

  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name'  => 'Migrate uploads',
      'description'  => 'Uploads migration',
      'group' => 'Migrate Drupal',
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();
    $migration = entity_load('migration', 'd6_upload_field');
    $executable = new MigrateExecutable($migration, $this);
    $executable->import();
    $dumps = array(
      $this->getDumpDirectory() . '/Drupal6UploadField.php',
    );
    $this->prepare($migration, $dumps);
  }

  /**
   * Tests the Drupal 6 upload settings to Drupal 8 field migration.
   */
  public function testUpload() {
    $field = entity_load('field_config', 'node.upload');
    $this->assertEqual($field->id(), 'node.upload');
    $this->assertEqual(array('node', 'upload'), entity_load('migration', 'd6_upload_field')->getIdMap()->lookupDestinationID(array('')));
  }

}
