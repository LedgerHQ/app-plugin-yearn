import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, nano_models, txFromEtherscan} from './test.fixture';

const BASE_SCREENS_S = 6
const BASE_SCREENS_X = 4

nano_models.forEach(function(model) {
  test('[Nano ' + model.letter + '] Claim Lab yveCRV', zemu(model, async (sim, eth) => {
    // Original TX: https://etherscan.io/tx/0xaf21fe6f80cfbad8ee0f3de8c4795f2f78afd6a85ad4237239fdd286b7f71934
    const serializedTx = txFromEtherscan("0x"+"02f870017c8459682f00851e7750d2fb8301947694c5bddf9843308380375a611c18b50fb9341f502a80844e71d92dc001a04021dc9052d3a5eb333afc42b80b05480a7ae30bac4fa848bd56dad48ca4d1d2a0126233c940eb0fa2b6818d6c32605350d3251af288e47fc3e07d8e7d17002deb");

    const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);
    const right_clicks = model.letter === 'S' ? BASE_SCREENS_S : BASE_SCREENS_X;
    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_claim_yveCRV', [right_clicks, 0]);
    await tx;
  }));
});
