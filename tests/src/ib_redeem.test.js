import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 2 + 1 + 3 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE

test('[Nano S] IB Redeem', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x5af50ad7f1b6f740a81db07e450f597a9d837426b33b1dd1647184485402c3f4
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f89001318459682f00851786912742830472be9441c84c0e2ee0b740cf0d31f63f3b6f627dc6b39380a4db006a750000000000000000000000000000000000000000000000000000000b6c399b59c001a069b59a00939dd4d0be0187294305dc7c4b67d0a2accf1db4a53bdb05111aca1aa04433c084d911ff53cd78d633138003c1e18b75b85734c9bd93dbacb947bd5dee"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_ib_redeem', [BASE_SCREENS_S, 0]);
}));



test('[Nano S] IB Redeem', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0x5af50ad7f1b6f740a81db07e450f597a9d837426b33b1dd1647184485402c3f4
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f89001318459682f00851786912742830472be9441c84c0e2ee0b740cf0d31f63f3b6f627dc6b39380a4db006a750000000000000000000000000000000000000000000000000000000b6c399b59c001a069b59a00939dd4d0be0187294305dc7c4b67d0a2accf1db4a53bdb05111aca1aa04433c084d911ff53cd78d633138003c1e18b75b85734c9bd93dbacb947bd5dee"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_ib_redeem', [BASE_SCREENS_X, 0]);
}));
