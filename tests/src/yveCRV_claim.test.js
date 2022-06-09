import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu } from './test.fixture';

const BASE_SCREENS_S = (1 + 1 + 3 + 1) //YEARN + AMOUNT + GAS_FEES + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + APPROVE

// Nanos S test
test('[Nano S] Claim Lab yveCRV', zemu("nanos", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xaf21fe6f80cfbad8ee0f3de8c4795f2f78afd6a85ad4237239fdd286b7f71934
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f870017c8459682f00851e7750d2fb8301947694c5bddf9843308380375a611c18b50fb9341f502a80844e71d92dc001a04021dc9052d3a5eb333afc42b80b05480a7ae30bac4fa848bd56dad48ca4d1d2a0126233c940eb0fa2b6818d6c32605350d3251af288e47fc3e07d8e7d17002deb"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_claim_yveCRV', [BASE_SCREENS_S, 0]);
}));

test('[Nano X] Claim Lab yveCRV', zemu("nanox", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xaf21fe6f80cfbad8ee0f3de8c4795f2f78afd6a85ad4237239fdd286b7f71934
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f870017c8459682f00851e7750d2fb8301947694c5bddf9843308380375a611c18b50fb9341f502a80844e71d92dc001a04021dc9052d3a5eb333afc42b80b05480a7ae30bac4fa848bd56dad48ca4d1d2a0126233c940eb0fa2b6818d6c32605350d3251af288e47fc3e07d8e7d17002deb"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_claim_yveCRV', [BASE_SCREENS_X, 0]);
}));

test('[Nano SP] Claim Lab yveCRV', zemu("nanosp", async (sim, eth) => {
  // Original TX: https://etherscan.io/tx/0xaf21fe6f80cfbad8ee0f3de8c4795f2f78afd6a85ad4237239fdd286b7f71934
  eth.signTransaction(
    "44'/60'/0'/0/0",
    "02f870017c8459682f00851e7750d2fb8301947694c5bddf9843308380375a611c18b50fb9341f502a80844e71d92dc001a04021dc9052d3a5eb333afc42b80b05480a7ae30bac4fa848bd56dad48ca4d1d2a0126233c940eb0fa2b6818d6c32605350d3251af288e47fc3e07d8e7d17002deb"
  );

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_claim_yveCRV', [BASE_SCREENS_X, 0]);
}));
