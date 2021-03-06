--TEST--
InspectorFile onResolve/purge
--FILE--
<?php
$include = sprintf("%s/purge.inc", dirname(__FILE__));

$file = new class($include) extends Inspector\InspectorFile {
	public function onResolve() {
		unset($this->hook);

		$this->hook = new class($this->findFirstInstruction(Inspector\InspectorInstruction::ZEND_ADD)) extends
				Inspector\InspectorBreakPoint {

			public function hit(Inspector\InspectorFrame $frame) {
				echo "OK\n";
			}
		};
	}
};

$a = 10;
$b = 20;

include($include);

Inspector\InspectorFile::purge([__FILE__]);

include($include);
?>
--EXPECT--
OK
OK
