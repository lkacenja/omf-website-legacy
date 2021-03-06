<?php

/**
 * @file
 * Contains \Drupal\Tests\Core\DependencyInjection\DependencySerializationTest.
 */

namespace Drupal\Tests\Core\DependencyInjection;

use Drupal\Core\DependencyInjection\Container;
use Drupal\Core\DependencyInjection\DependencySerializationTrait;
use Drupal\Tests\UnitTestCase;
use Symfony\Component\DependencyInjection\ContainerAwareInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Tests the dependency serialization trait.
 *
 * @coversDefaultClass \Drupal\Core\DependencyInjection\DependencySerializationTrait
 */
class DependencySerializationTest extends UnitTestCase {

  /**
   * {@inheritdoc}
   */
  public static function getInfo() {
    return array(
      'name' => '\Drupal\Core\DependencyInjection\DependencySerializationTrait unit test',
      'description' => '',
      'group' => 'System'
    );
  }

  /**
   * @covers ::__sleep
   * @covers ::__wakeup
   */
  public function testSerialization() {
    // Create a pseudo service and dependency injected object.
    $service = new \stdClass();
    $service->_serviceId = 'test_service';
    $container = new Container();
    $container->set('test_service', $service);
    $container->set('service_container', $container);
    \Drupal::setContainer($container);

    $dependencySerialization = new DependencySerializationTestDummy($service);
    $dependencySerialization->setContainer($container);

    $string = serialize($dependencySerialization);
    $object = unserialize($string);

    $string = serialize($dependencySerialization);
    /** @var \Drupal\Tests\Core\DependencyInjection\DependencySerializationTestDummy $object */
    $dependencySerialization = unserialize($string);

    $this->assertSame($service, $dependencySerialization->service);
    $this->assertSame($container, $dependencySerialization->container);
    $this->assertEmpty($dependencySerialization->getServiceIds());
  }

}

/**
 * Defines a test class which has a single service as dependency.
 */
class DependencySerializationTestDummy implements ContainerAwareInterface {

  use DependencySerializationTrait;

  /**
   * A test service.
   *
   * @var \stdClass
   */
  public $service;

  /**
   * The container.
   *
   * @var \Symfony\Component\DependencyInjection\ContainerInterface
   */
  public $container;

  /**
   * Constructs a new TestClass object.
   *
   * @param \stdClass $service
   *   A test service.
   */
  public function __construct(\stdClass $service) {
    $this->service = $service;
  }

  /**
   * {@inheritdoc}
   */
  public function setContainer(ContainerInterface $container = NULL) {
    $this->container = $container;
  }

  /**
   * Gets the stored service IDs.
   */
  public function getServiceIds() {
    return $this->_serviceIds;
  }
}
