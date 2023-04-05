
import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models } from './test.fixture';
import { ethers } from "ethers";
import { parseEther } from "ethers/lib/utils";

const BASE_SCREENS_S = 5
const BASE_SCREENS_X = 5

nano_models.forEach(function(model) {
  test('[Nano ' + model.letter + '] Deposit Tokens with Partner contract', zemu(model, async (sim, eth) => {
    const PARTNER_ID_ADDR = "0xB8c93dF4E1e6b1097889554D9294Dfb42814063a";
    const DAI_CONTRACT_ADDR = "0xdA816459F1AB5631232FE5e97a05BBBb94970c95";
    const AMOUNT_TO_DEPOSIT = '60000000000000000000'; // 60
    const contractAddr = '0x8ee392a4787397126c163cb9844d7c447da419d8';
    const contract = new ethers.Contract(contractAddr, ['function deposit(address,address,uint256)']);
    const {data} = await contract.populateTransaction['deposit(address,address,uint256)'](
      DAI_CONTRACT_ADDR, PARTNER_ID_ADDR, AMOUNT_TO_DEPOSIT
    );

    let unsignedTx = genericTx;
    unsignedTx.to = contractAddr;
    unsignedTx.data = data;
    unsignedTx.value = parseEther("0.1");
    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
    const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);
    const right_clicks = model.letter === 'S' ? BASE_SCREENS_S : BASE_SCREENS_X;
    await waitForAppScreen(sim);
    await sim.navigateAndCompareSnapshots('.', model.name + '_deposit_partner', [right_clicks, 0]);
    await tx;
  }));
});
