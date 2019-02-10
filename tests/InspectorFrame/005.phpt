--TEST--
InspectorFrame getSymbols
--FILE--
<?php
use Inspector\InspectorFunction;
use Inspector\InspectorBreakPoint;
use Inspector\InspectorFrame;

function foo($a, $b) {
	$a + $b;
}

$inspector = 
	new InspectorFunction("foo");

$opline = $inspector->getInstruction(2);

$break = new class($opline) extends InspectorBreakPoint {
	public function hit(InspectorFrame $frame){
		$symbols = $frame->getPrevious()->getPrevious()->getSymbols();
		if (isset($symbols["inspector"])) {
			echo "OK";
		}
	}
};

function test($function) {
	$function(1, 2);
}

test("foo");
?>
--EXPECT--
OK

